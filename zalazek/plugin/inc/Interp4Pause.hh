#ifndef  COMMAND4PAUSE_HH
#define  COMMAND4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Pause
 *
 * Plik zawiera definicję klasy Interp4Pause.
 */

/*!
 * \brief Zatrzymuje prace danego watku interpretera na okreslony czas
 *
 * Klasa zatrzymuje prace danego watku interpretera na okreslony czas.
 */
class Interp4Pause: public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */

  /*!
   * \brief Czas trwania zatrzymania watku wyrazony w milisekundach
   */
  double  _Pause_time;
 public:
  /*!
   * \brief Konstruktor obiektu klasy
   */
  Interp4Pause();
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
