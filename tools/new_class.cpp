
#include "NewName.hpp"

NewName::NewName() 						{	this->_val = 0;	}

NewName::~NewName()						{}

NewName::NewName(NewName const &src)	{	static_cast<void>src;	}

std::ostream &operator<<(std::ostream &o, NewName &c) {
	o << "I'm NewName class " << c.getValue();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		NewName::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////
void	NewName::empty() {

}
