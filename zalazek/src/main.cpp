#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <list>
#include <thread>
#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include <memory>
#include <list>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "../inc/Interp4Command.hh"
#include "../inc/Set4LibInterfaces.hh"
#include "../inc/Scene.hh"
#include "../inc/MobileObj.hh"
#include "../inc/xmlinterp.hh"
#include "../inc/Port.hh"
#include "../inc/AccessControl.hh"
#include "../inc/Sender.hh"


#define LINE_SIZE 500

using namespace std;
using namespace xercesc;

void Fun_CommunicationThread(Sender  *pSender)
{
  pSender->Watching_and_Sending();
}

bool ExecCmd(GeomObject *pObj, AccessControl  *pAccCtrl)
{
  bool Changed;

  while (true) {
    pAccCtrl->LockAccess();
    if (!(Changed = pObj->IncStateIndex())) { pAccCtrl->UnlockAccess();  break; }
    pAccCtrl->MarkChange();
    pAccCtrl->UnlockAccess();
    usleep(300000);
  }
  return true;
}

bool ExecActions(istream &rIStrm, Set4LibInterfaces t_plugins){

  string keyStr;
  shared_ptr<LibInterface> auxInterface;
  void *pFun;
  void *pLibHnd;
  Interp4Command *(*pCreateCmd)(void);

  string libName;

  rIStrm >> keyStr;

  if (t_plugins.Find(keyStr.c_str(), auxInterface)){


    cout << endl;
    cout << "Found command: " << keyStr.c_str() << endl;

    libName = "libInterp4" + keyStr + ".so";

    pLibHnd = dlopen(libName.c_str(), RTLD_LAZY);
  }
  else
    return false;

  pFun = dlsym(pLibHnd, "CreateCmd");
  pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
  Interp4Command *pCmd = pCreateCmd();

  if(!(pCmd->ReadParams(rIStrm)))
    return false;

  cout << "----- Parameters -----" << endl;
  pCmd->PrintCmd();
  cout << endl;


  delete pCmd;
  dlclose(pLibHnd);

  return true;
}

bool Read_XML(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {

     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}

bool ExecProcessor( const char *NazwaPliku, istringstream &IStrm4Cmds ){
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc) return false;

  while(fgets(Line,LINE_SIZE,pProc)){
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());

  return pclose(pProc) == 0;
}


bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }

  cout << "Nawiazano polaczenie z serwerem " << endl;
  return true;
}


int main(int argc, char** argv)
{
  Configuration Config;
  Scene Scene1;

  std::shared_ptr<MobileObj> obj1 = make_shared<MobileObj>();

  Set4LibInterfaces PluginInterfaces;
  istringstream IStrm;
  if(argc < 2){
    cerr << endl;
    cerr << "Za malo parametrow " << endl;
    cerr << endl;
    return 1;
  }



  if(!ExecProcessor(argv[1],IStrm)){
    cerr << endl;
    cerr << "Blad" << endl;
    cerr << endl;
    return 2;
  }


  cout << "----- Odczyt XML START -----" << endl;

  if (!Read_XML("config/config.xml",Config)) return 3;

  cout << "----- Odczyt XML KONIEC -----" << endl<<endl;
  cout << "----- Odczyt parametrow START -----" << endl;


  cout << "Wewnątrz pliku: " << endl;
  cout << endl << IStrm.str() << endl;

  shared_ptr<LibInterface> Interface4Move = make_shared<LibInterface>("libInterp4Move.so");
  shared_ptr<LibInterface> Interface4Set = make_shared<LibInterface>("libInterp4Set.so");
  shared_ptr<LibInterface> Interface4Rotate = make_shared<LibInterface>("libInterp4Rotate.so");
  shared_ptr<LibInterface> Interface4Pause = make_shared<LibInterface>("libInterp4Pause.so");

  PluginInterfaces.AddToSet(Interface4Move);
  PluginInterfaces.AddToSet(Interface4Set);
  PluginInterfaces.AddToSet(Interface4Rotate);
  PluginInterfaces.AddToSet(Interface4Pause);

  while(ExecActions(IStrm, PluginInterfaces) == true){}

  cout << "----- Odczyt parametrow KONIEC -----" << endl << endl;
  cout << "Polaczenie z serwerem " << endl;

  cout << "Port: " << PORT << endl;

  int Socket4Sending;

  if (!OpenConnection(Socket4Sending)) return 4;

  Sender ClientSender(Socket4Sending, &Scene1);


  thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);


  for (GeomObject &rObj : Scene1._Container4Objects) {
    cout << "Wykonano petle" << endl;
    usleep(20000);
    ExecCmd(&rObj,&Scene1);
    Scene1.MarkChange();
    usleep(100000);
  }
  usleep(100000);


  cout << "Close\n" << endl;
  Send(Socket4Sending,"Close\n");
  ClientSender.CancelCountinueLooping();
  Thread4Sending.join();
  close(Socket4Sending);

  return 0;
}
