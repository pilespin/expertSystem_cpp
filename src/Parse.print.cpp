
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"
#include "mylib.hpp"

//////////////////////////////////  PRINT  ////////////////////////////////////

void	Parse::printAllElement() {

	for (auto it = this->mapElem.begin(); it != this->mapElem.end(); it++)
	{	
		std::cout << it->second;
	}
}

void	Parse::printTrueElement() {

	if (this->mapElem.size())
		std::cout << "Is True:" << std::endl;
	for (auto it = this->mapElem.begin(); it != this->mapElem.end(); it++)
	{	
		if (it->second.getValue() == eValue::True)

			std::cout << it->second.getName() << std::endl;
	}
}

void	Parse::printRule() {

	std::cout << "rule: " << std::endl;
	for (auto it = this->rule.begin() ; it != this->rule.end() ; it++)
	{
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "elem:      " << '"' << it->elem << '"' << std::endl;
		std::cout << "implies:   " << '"' << Enum::getImplication(it->implies) << '"' << std::endl;
		std::cout << "impliqued: " << '"' << it->impliqued << '"' << std::endl;
		std::cout << std::endl;

		std::cout << "item size:  " << it->item.size() << std::endl;
		for (auto it1 = it->item.begin(); it1 != it->item.end(); it1++)
		{
			std::cout << "item:      " << '"' << *it1 << '"' << std::endl;
		}
		std::cout << "optr size:  " << it->optr.size() << std::endl;
		for (auto it1 = it->optr.begin(); it1 != it->optr.end(); it1++)
		{
			std::cout << "optr:      " << Enum::getLogicOperator(*it1) << std::endl;
		}
		std::cout << "-----------------------------------" << std::endl;
	}
}

void	Parse::printFact() {

	for (auto it = this->fact.begin() ; it != this->fact.end() ; ++it)
	{
		std::cout << "fact: " << '"' << *it << '"' << std::endl;
	}

	for (auto it = this->allfact.begin(); it != this->allfact.end(); it++) {
		std::cout << '"' << *it << '"'  <<std::endl;
	}
}

void	Parse::printQueries() {

	// for (auto it = this->querie.begin() ; it != this->querie.end() ; ++it)
	// {
		// std::cout << "querie: " << '"' << *it << '"' <<  std::endl;
	// }
	for (auto it = this->allquerie.begin(); it != this->allquerie.end(); it++) {
		std::cout << *it << " = ";
		if (getMagicTransformUndefinedToFalse() && getElement(*it)->getValue() == eValue::Undefined)
			std::cout << Enum::getValue(eValue::False) << std::endl;
		else
			std::cout << Enum::getValue(getElement(*it)->getValue()) << std::endl;
	}
}
