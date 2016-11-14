
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
		std::cout << "Fact: " << *it << std::endl;
		if (this->mapElem.count(*it))
		{
			this->mapElem[*it].setDefaultValue(eValue::True);
		}
	}
}

Element *Parse::getElement(std::string elem) {
	if (this->mapElem.count(elem))
		return (&this->mapElem[elem]);
	else
		throw Msg("Error get element in map");
	// return (nullptr);
}

void	Parse::setValueAtElement(std::string elem, eValue val) {

	Element *e = getElement(elem);
	
	if (e)
		e->setValue(val);
	else
		throw Msg("Error get element in map");

}
