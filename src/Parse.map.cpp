
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"

void 	Parse::insertIntoMap(std::string tmp) {
	if (tmp.find_first_of("!") == 0)
		tmp.erase(0, 1);
	this->mapElem[tmp] = Element(tmp, eValue::Undefined);
}

void	Parse::createMap() {

	std::string tmp;

	for (auto it = this->rule.begin() ; it != this->rule.end() ; it++) {
		for (auto it1 = it->item.begin() ; it1 != it->item.end() ; it1++) {
			insertIntoMap(*it1);
		}
		insertIntoMap(it->impliqued);
	}
}

void	Parse::setInitialFact() {

	for (auto it = this->allfact.begin(); it != this->allfact.end(); it++)
	{
		if (this->mapElem.count(getGoodName(*it)))
		{
			this->mapElem[getGoodName(*it)].setDefaultValue(this->getGoodValue(*it, eValue::True));
		}
	}
}

Element *Parse::getElement(std::string elem) {
	elem = this->getGoodName(elem);
	if (this->mapElem.count(elem))
	{
		return (&this->mapElem[elem]);
	}
	else
		throw Msg("Error get element in map");
}

void	Parse::setValueAtElement(std::string elem, eValue val) {

	Element *e = getElement(elem);
	
	if (e)
		e->setValue(val);
	else
		throw Msg("Error get element in map");

}
