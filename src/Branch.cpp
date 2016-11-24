
#include "Branch.hpp"

Branch::Branch() 						{	this->_val = 0;	}
Branch::Branch(std::string name, eNegative negative, eLogicOperator logicOperator,
	eValue value, eImplication implies, 
	Branch *left, Branch *right){
	init();
	this->name 			= name;
	this->negative 		= negative;
	this->logicOperator	= logicOperator;
	this->value 		= value;
	this->implies 		= implies;
	this->left 			= left;
	this->right 		= right;		
}

Branch::Branch(std::string name, eNegative negative, eValue value) {
	init();
	this->name 			= name;
	this->negative 		= negative;
	this->value 		= value;
}  

void 		Branch::init() {
	this->_val 			= 0;
	this->name 			= "";
	this->negative 		= eNegative::False;
	this->logicOperator	= eLogicOperator::None;
	this->value 		= eValue::Undefined;
	this->implies 		= eImplication::Simple;
	this->left 			= NULL;
	this->right 		= NULL;
}

Branch::~Branch()						{}

// Branch::Branch(Branch const &src)	{	
// 	this->_val = src._val;
// }

// Branch		&Branch::operator=(Branch const &rhs) {

// 	if (this != &rhs)
// 	{
// 		this->_val = rhs._val;
// 	}
// 	return (*this);
// }

std::ostream &operator<<(std::ostream &o, Branch &c) {
	o << "Branch: " << c.getEmpty() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
void		Branch::setValue(eValue value)	{	this->value = value;	}
int			Branch::getEmpty() const		{	return (this->_val);	}
eValue		Branch::getValue() const		{	return (this->value);	}
std::string	Branch::getName() const			{	return (this->name);	}
///////////////////////////////////////////////////////////////////////////////

void		Branch::calcResult() {

	if (right->getValue() == eValue::Undefined)
		this->calcCore(right);

	if (left->getValue() == eValue::Undefined)
		this->calcCore(left);

	this->calcCore(this);

}

void		Branch::calcCore(Branch *branch) {

	if (branch->logicOperator == eLogicOperator::Et)
	{
		if ((branch->left->getValue() == eValue::True) && 
			(branch->right->getValue() == eValue::True))
		{
			branch->setValue(eValue::True);
		}
	}
	else if (branch->logicOperator == eLogicOperator::Ou)
	{
		if ((branch->left->getValue() == eValue::True) || 
			(branch->right->getValue() == eValue::True))
		{
			branch->setValue(eValue::True);
		}
	}
	else if (branch->logicOperator == eLogicOperator::Xor)
	{
		if ((branch->left->getValue() == eValue::True) ^
			(branch->right->getValue() == eValue::True))
		{
			branch->setValue(eValue::True);
		}
	}
	else if (branch->logicOperator == eLogicOperator::None)
	{
	}
	else
		throw Msg("Error: WTF !!! What's this logic operator !!!");
}

void		Branch::print() {

	if (this->left && this->right)
	{

		std::cout << std::endl;
		std::cout << this->name << std::endl;
		std::cout << this->getName() << " = " << Enum::getValue(this->getValue()) << std::endl;
		std::cout << "|" << std::endl;
		std::cout << this->left->getName() << " = " << Enum::getValue(this->left->getValue()) << " ." << Enum::getLogicOperator(this->logicOperator) << ". "; 
		std::cout << this->right->getName() << " = " << Enum::getValue(this->right->getValue()) << std::endl;
	}
}

void		Branch::empty() {

}
