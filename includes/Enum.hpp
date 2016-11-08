
#pragma once

#include <project.hpp>

enum class eValue		 	{False, True, Undefined};
enum class eNegative	 	{False, True};
enum class eImplication 	{Simple, Double};
enum class eLogicOperator	{Et, Ou, Xor, None};

class Enum {

public:
	Enum();
	~Enum();
	Enum(Enum const &src);
	Enum &operator=(Enum const &rhs);

	static 	std::string		getLogicOperator(eLogicOperator logicOperator);
	static 	eLogicOperator	getLogicOperator(std::string str);
	static 	std::string		getValue(eValue value);
	static 	std::string		getImplication(eImplication value);

	int			getValue() const;
	void		empty();

	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

private:
	int _val;
};

std::ostream &operator<<(std::ostream &o, Enum &c);
