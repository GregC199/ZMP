#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set.
 */

/*!
 * \brief Modeluje polecenie dla obiektu mobilnego, ktore generuje obiekt na scenie, w okreslonym polozeniu
 *
 *  Klasa modeluje ustawienie obiektu mobilnego na scenie w okreslonym polozeniu.
 */
class Interp4Set: public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  /*!
   * \brief Wspolrzedna X polozenia obiektu na scenie
   */
  double  _Coordinate_X;
  /*!
   * \brief Wspolrzedna Y polozenia obiektu na scenie
   */
  double  _Coordinate_Y;
  /*!
   * \brief Kat orientacji obiektu wokol osi OZ
   */
  double  _Rot_OZ;
  /*!
   * \brief Nazwa inicjalizowanego obiektu
   */
  std::string _name;
 public:
  /*!
   * \brief Konstruktor obiektu klasy
   */
  Interp4Set();
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( MobileObj  *pMobObj, int Socket) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
