#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief Utworzenie polecenia Pause
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 * \brief Konstruktor z inicjalizacja parametrow
 *
 */
Interp4Pause::Interp4Pause(): _Pause_time(0)
{}


/*!
 * \brief Funkcja wyswietla polecenie i parametry
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
	cout << GetCmdName() << " " <<_Pause_time<< endl;
}


/*!
 * \brief Funkcja zwracajaca nazwe polecenia
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Funkcja wykonujaca polecenie
 *
 */
bool Interp4Pause::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 * \brief Funkcja wczytujaca zadane parametry z polecenia
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
	Strm_CmdsList >> _Pause_time;

	return (!Strm_CmdsList.fail());

	return true;
}


/*!
 * \brief Funkcja tworzaca nowe polecenie
 *
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


/*!
 * \brief Funkcja wyswietlajaca skladnie polecenia
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause    DlugoscCzasuWstrzymaniaSymulacji[ms]" << endl;
}
