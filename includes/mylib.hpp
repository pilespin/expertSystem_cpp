
#pragma once

#include <iostream>

class mylib {

public:
	mylib();
	~mylib();
	mylib(mylib const &src);
	mylib &operator=(mylib const &rhs);

///////////////////////////////////////////////////////////////////////////////
	int			getValue() const;
	void		empty();
///////////////////////////////////////////////////////////////////////////////

	static std::string 	trim(std::string str);
	static double	 	utime();

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

std::ostream &operator<<(std::ostream &o, mylib &c);
