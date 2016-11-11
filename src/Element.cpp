
#include "Element.hpp"

Element::Element() 						{	this->_val = 0;	}

Element::Element(std::string name, eValue value) {
	this->_val = 0;
	this->name = name;
	this->value = value;
	this->defaultValue = value;
}


Element::~Element()						{}

Element::Element(Element const &src)	{	
	this->_val = src._val;
	this->name = src.name;
	this->value = src.value;
	this->defaultValue = src.value;
}

Element	&Element::operator=(Element const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
		this->_val = rhs._val;
		this->name = rhs.name;
		this->value = rhs.value;
		this->defaultValue = rhs.value;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Element &c) {
	o << "Name:             " << '"' << c.getName() << '"' << std::endl;
	o << "Value:            " << Enum::getValue(c.getValue()) << " " << std::endl;
	o << "Value by default: " << Enum::getValue(c.getDefaultValue()) << " " << std::endl;
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int				Element::getEmpty() const			{	return (this->_val);			}
eValue			Element::getValue() const			{	return (this->value);			}
eValue			Element::getDefaultValue() const	{	return (this->defaultValue);	}
std::string		Element::getName() const			{	return (this->name);			}
///////////////////////////////////////////////////////////////////////////////

void	Element::empty() {

}
