#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief Utworzenie polecenia Rotate
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 * \brief Konstruktor z inicjalizacja parametrow
 *
 */
Interp4Rotate::Interp4Rotate(): _name("obj"), _Angular_Speed(0), _Angle(0)
{}


/*!
 * \brief Funkcja wyswietla polecenie i parametry
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
	cout << GetCmdName() << " "  << _name  <<" " << _Angular_Speed << " " << _Angle << endl;
}


/*!
 * \brief Funkcja zwracajaca nazwe polecenia
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Funkcja wykonujaca polecenie
 *
 */
bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
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
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

	Strm_CmdsList >> _name >> _Angular_Speed >> _Angle;

	return (!Strm_CmdsList.fail());

}


/*!
 * \brief Funkcja tworzaca nowe polecenie
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 * \brief Funkcja wyswietlajaca skladnie polecenia
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu SzybkoscKatowa[stopnie/s] KatObrotu[stopnie]" << endl;
}
