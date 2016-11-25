
#include "NewName.hpp"

NewName::NewName() 						{	this->_val = 0;	}

NewName::~NewName()						{}

NewName::NewName(NewName const &src)	{	static_cast<void>src;	}

std::ostream &operator<<(std::ostream &o, NewName &c) {
	o << "I'm NewName class " << c.getEmpty();
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		NewName::getEmpty() const	{	return (this->nothing);	}
///////////////////////////////////////////////////////////////////////////////
void	NewName::empty() {

}
