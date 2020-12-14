#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <string>
#include <iostream>
#include <cassert>
#include <dlfcn.h>

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface ...
 */

/*!
 * \brief Modeluje interfejs dla dynamicznej biblioteki
 *
 *  Klasa modeluje ...
 */

class LibInterface{
  /*!
   * \brief Uchwyt do biblioteki
   */
	void* _LibHandler;

  /*!
   * \brief Nazwa polecenia sluzaca do identyfikacji danej biblioteki
   */
	std::string _CmdName;

  /*!
   * \brief Wskaznik do nowego obiektu biblioteki
   */
	Interp4Command *(*_pCreateCmd)(void);

public:

  /*!
   * \brief Funkcja umozliwia odczytanie parametrow oraz ich zapis
   */
	bool ReadParams(std::istream &InStrm){
		return _pCreateCmd()->ReadParams(InStrm);
	}


  /*!
   * \brief Funkcja wyswietla nazwe polecenia oraz parametry
   */
	void PrintCmd(){
		_pCreateCmd()->PrintCmd();
	}


	/*!
	 * \brief Konstruktor obiektu klasy
	 *
	 * Konstruktor wpierw sprawdza istnienie danej biblioteki, probujac ja utworzyc poprzez "Lazy binding".
	 * Nastepnie sprawdzamy czy dana biblioteka posiada polecenie "CreateCmd". Jesli tak to tworzymy ja
	 * i zapisujemy jej nazwe do zmiennej /param _LibHandler
	 */
	LibInterface(const std::string _LibName){
		void* PFun;

		this->_LibHandler = dlopen(_LibName.c_str(), RTLD_LAZY);
		if(!(this->_LibHandler)) {
			std::cerr << "Brak biblioteki "<< _LibName << "!" << std::endl;
		}
		else{
			PFun = dlsym(this->_LibHandler,"CreateCmd");
			if (!PFun) {
				std::cerr << "Blad! Nie znaleziono polecenia CreateCmd dla wtyczki " << _LibName << "!" << std::endl;
			}
			else{
				_pCreateCmd = * reinterpret_cast<Interp4Command* (**)(void)>(&PFun);
				this->_CmdName = _pCreateCmd()->GetCmdName();
			}
		}
	  }



  /*!
   * \brief Funkcja zwraca nazwe polecenia
   */
	const std::string GetCmdName(){
		return _CmdName;
	}

};

#endif
