#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief Utworzenie polecenia Move
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 * \brief Konstruktor z inicjalizacja parametrow
 *
 */
Interp4Move::Interp4Move(): _name("obj"), _Speed(0), _Distance(0)
{}


/*!
 * \brief Funkcja wyswietla polecenie i parametry
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
	cout << GetCmdName() << " " << _name << " " << _Speed<< " "
	       << _Distance << endl;
}


/*!
 * \brief Funkcja zwracajaca nazwe polecenia
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Funkcja wykonujaca polecenie
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
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
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
	Strm_CmdsList >> _name  >>_Speed >>_Distance;

	return (!Strm_CmdsList.fail());
}


/*!
 * \brief Funkcja tworzaca nowe polecenie
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 * \brief Funkcja wyswietlajaca skladnie polecenia
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
