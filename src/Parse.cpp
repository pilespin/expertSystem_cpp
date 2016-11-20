
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"

Parse::Parse() {	
	this->_val = 0;
	this->multipleCharInElement = false;
	this->transformUndefinedToFalse = false;
}

Parse::~Parse()					{}

Parse::Parse(Parse const &src)	{	
	this->_val = src._val;
}

Parse	&Parse::operator=(Parse const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Parse &c) {
	o << "I'm Parse class" << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Parse::getValue() const						{	return (this->_val);						}
bool	Parse::getMultipleCharInElement()			{	return (this->multipleCharInElement);		}
bool	Parse::getMagicTransformUndefinedToFalse()	{	return (this->transformUndefinedToFalse);	}

void	Parse::setMultipleCharInElement() 			{	this->multipleCharInElement = true;			}
void	Parse::setMagicTransformUndefinedToFalse() 	{	this->transformUndefinedToFalse = true; 	}
///////////////////////////////////////////////////////////////////////////////

void	Parse::init() {

	this->calcRule();
	this->createMap();
	this->getFact();
	this->getQuerie();
	this->setInitialFact();

}

bool	Parse::checkIsNegative(std::string elem) {
	if (elem.find_first_of("!") == 0)
	{
		return (true);
	}
	return (false);
}

std::string	Parse::getGoodName(std::string elem) {
	if (checkIsNegative(elem))
	{
		elem.erase(0, 1);
	}
	// std::cout << "GetGoodName : " << elem << std::endl;

	return (elem);
}

eValue		Parse::getGoodValue(std::string elem, eValue val) {	

	if (getMagicTransformUndefinedToFalse())
	{
		if (val == eValue::Undefined)
			val = eValue::False;
	}
	if (checkIsNegative(elem))
	{
		return (Enum::getOpositeValue(val));
	}
	return (val);
}

eValue		Parse::compute(eValue one, eLogicOperator optr, eValue two) {	

	if (optr == eLogicOperator::Et)
	{
		if (one == eValue::True && two == eValue::True)
		{
			return (eValue::True);
		}
	}
	else if (optr == eLogicOperator::Ou)
	{
		if (one == eValue::True || two == eValue::True)
		{
			return (eValue::True);
		}
	}
	else if (optr == eLogicOperator::Xor)
	{
		// if ((one == eValue::True) ^ (two == eValue::True)) 
		if ((one == eValue::True && two == eValue::False) ||
			(one == eValue::False && two == eValue::True))
		{
			return (eValue::True);
		}
	}
	return (eValue::Undefined);
}

///////////////////////////////////// ELSE ////////////////////////////////////

void	Parse::empty() {

}
