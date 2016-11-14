
#include "Enum.hpp"

Enum::Enum() 						{	this->_val = 0;	}

Enum::~Enum()						{}

Enum::Enum(Enum const &src)	{
	this->_val = src._val;
}

Enum	&Enum::operator=(Enum const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Enum &c) {
	o << "Enum: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Enum::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////

std::string 	Enum::getLogicOperator(eLogicOperator logicOperator)
{
	std::vector<std::string> e {"Et", "Ou", "Xor", "None"};
	return (e[static_cast<int>(logicOperator)]);
}

eLogicOperator	Enum::getLogicOperator(std::string str)
{
	if (!str.compare("+"))
		return (eLogicOperator::Et);
	else if (!str.compare("|"))
		return (eLogicOperator::Ou);
	else if (!str.compare("^"))
		return (eLogicOperator::Xor);
	else
		throw Msg("Error: When converting string to Enum eLogicOperator");
}

std::string 	Enum::getValue(eValue value)
{
	std::vector<std::string> e {"False", "True", "Undefined"};
	return (e[static_cast<int>(value)]);
}

std::string 	Enum::getImplication(eImplication value)
{
	std::vector<std::string> e {"Simple", "Double"};
	return (e[static_cast<int>(value)]);
}

eValue			Enum::getOpositeValue(eValue value){
	if (value == eValue::True)
		return (eValue::False);
	else if (value == eValue::False)
		return (eValue::True);
	else
		return (value);
}


void			Enum::empty() {

}
