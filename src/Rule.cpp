
#include <project.hpp>
#include "Rule.hpp"

Rule::Rule() 						{	this->_val = 0;	}

Rule::Rule(std::string elem, eImplication implies, std::string impliqued) {
	this->_val = 10;
	this->elem = elem;
	this->implies = implies;
	this->impliqued = impliqued;
}

Rule::~Rule()						{}

Rule::Rule(Rule const &src)	{	
	this->_val = src._val;
	this->elem = src.elem;
	this->implies = src.implies;
	this->impliqued = src.impliqued;
}

// Rule	&Rule::operator=(Rule const &rhs) {

// 	if (this != &rhs)
// 	{
// 		this->_val = rhs._val;
// 		this->elem = rhs.elem;
// 		this->implies = rhs.implies;
// 		this->impliqued = rhs.impliqued;
// 	}
// 	return (*this);
// }

std::ostream &operator<<(std::ostream &o, Rule &c) {
	o << "Rule: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Rule::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////
void	Rule::empty() {

}
