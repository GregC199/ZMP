#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief Utworzenie polecenia Set
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 * \brief Konstruktor z inicjalizacja parametrow
 *
 */
Interp4Set::Interp4Set(): _name("obj"), _Coordinate_X(0), _Coordinate_Y(0), _Rot_OZ(0)
{}


/*!
 * \brief Funkcja wyswietla polecenie i parametry
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
	cout << GetCmdName() << " " << _name << " " << _Coordinate_X << " " << _Coordinate_Y << " " << _Rot_OZ << endl;
}


/*!
 * \brief Funkcja zwracajaca nazwe polecenia
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Funkcja wykonujaca polecenie
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
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
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
	Strm_CmdsList >> _name >> _Coordinate_X >> _Coordinate_Y >> _Rot_OZ;

	return (!Strm_CmdsList.fail());
}


/*!
 * \brief Funkcja tworzaca nowe polecenie
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 * \brief Funkcja wyswietlajaca skladnie polecenia
 *
 */
void Interp4Set::PrintSyntax() const
{
	cout << "   Set  NazwaObiektu  WspolrzednaX[mm] WspolrzednaY[mm] KatObrotu[stopnie]" << endl;
}
