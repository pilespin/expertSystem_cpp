
#pragma once

#include <project.hpp>

class Rule {

public:
	Rule(std::string elem, eImplication implies, std::string impliqued);
	Rule();
	~Rule();
	Rule(Rule const &src);
	Rule &operator=(Rule const &rhs);

	int			getValue() const;
	void		empty();

	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

public:
	int 			_val;
	std::string 	elem;
	eImplication	implies;
	std::string 	impliqued;

	std::vector<std::string> 	item;
	std::vector<eLogicOperator> optr;
};

std::ostream &operator<<(std::ostream &o, Rule &c);
