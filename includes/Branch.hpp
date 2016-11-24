
#pragma once

#include <project.hpp>

class Branch {

public:
	Branch();
	Branch(std::string name, eNegative negative, eLogicOperator logicOperator,
		eValue evalue, eImplication eimplication, 
		Branch *left, Branch *right);
	Branch(std::string name, eNegative negative, eValue value);
	~Branch();
	// Branch(Branch const &src);
	// Branch &operator=(Branch const &rhs);

	void		setValue(eValue value);
	int			getEmpty() const;
	eValue		getValue() const;
	std::string	getName() const;
	void		empty();
	void		calcResult();
	void		print();

	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

private:
	void		init();
	void		calcCore(Branch	*branch);

	int 			_val;
	std::string 	name;
	eNegative		negative;
	eLogicOperator	logicOperator;
	// eValue 			defaultValue;
	eValue 			value;
	eImplication 	implies;
	Branch	 		*left;
	Branch	 		*right;
};

std::ostream &operator<<(std::ostream &o, Branch &c);
