#include "Scene.hh"

using namespace std;


int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}



class Sender {

   volatile bool    _ContinueLooping = true;

   int             _Socket = 0;

   Scene          *_pScn = nullptr;

  
 public:

   Sender(int Socket, Scene *pScn): _Socket(Socket), _pScn(pScn) {}


   bool ShouldCountinueLooping() const { return _ContinueLooping; }

   void CancelCountinueLooping() { _ContinueLooping = false; }

   void Watching_and_Sending() {
     while (ShouldCountinueLooping()) {
       if (!_pScn->IsChanged())  { usleep(10000); continue; }
       _pScn->LockAccess();
       
       Send(_Socket,"Clear\n");
       cout << "Clear\n";
       for (const GeomObject &rObj : _pScn->_Container4Objects) {

	 cout << rObj.GetStateDesc();
         Send(_Socket,rObj.GetStateDesc());
       }
       Send(_Socket,"Display\n");
       cout << "Display\n";
       
       _pScn->CancelChange();
       _pScn->UnlockAccess();
     }
   }
};
