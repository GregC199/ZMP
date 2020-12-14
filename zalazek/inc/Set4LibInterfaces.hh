#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <string>
#include <map>
#include <memory>
#include "LibInterfaces.hh"

using std::string;
using std::shared_ptr;
using std::pair;

/*!
 * \file
 * \brief Definicja klasy Set4LibInterfaces
 *
 * Plik zawiera definicję klasy Set4LibInterfaces,
 */


/*!
 * \brief Typ zestawu danych w postaci std::map<Key_Type,Mapped_Type>
 *
 * Typ ten modeluje zastaw danych posortowanych wzgledem klucza "Key_Type"
 */
typedef std::map<string, shared_ptr<LibInterface>> PluginSet;

/*!
 * \brief Klasa zestawu interfejsow do wtyczek
 *
 * Klasa modeluje zestaw interfejsow do wtyczek
 */
class Set4LibInterfaces{

	/*!
	* \brief  Mapa interfejsow wtyczek posortowanych wedlug klucza
	*
	*/
	PluginSet _PluginSet;
public:

	Set4LibInterfaces(){};
	/*!
	* \brief Metoda umozliwia dodanie interfejsu do mapy
	*
	*/
	void AddToSet(shared_ptr<LibInterface> &PLibInterface){
		_PluginSet.insert(pair<string, shared_ptr<LibInterface>>(PLibInterface->GetCmdName(), PLibInterface));
	}

	/*!
	* \brief Metoda umożliwia odnalezienie danego interfejsu w mapie
	*
	*/
	bool Find(string _LibName, shared_ptr<LibInterface> &PLib){
			auto it = _PluginSet.find(_LibName);

			if(it != _PluginSet.end()){
				PLib = it->second;
				return true;

			}
			else{
				return false;
			}
		}
};

#endif
