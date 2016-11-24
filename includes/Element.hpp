
#pragma once

#include <project.hpp>

class Element {

public:
	Element();
	Element(std::string name, eValue value);
	~Element();
	// Element(Element const &src);
	// Element &operator=(Element const &rhs);

	int			getEmpty() const;
	std::string	getName() const;
	eValue		getDefaultValue() const;
	eValue		getValue() const;
	// eValue		getGoodValue(std::string elem) const;
	// eValue		getGoodValue(std::string elem, eValue val) const;
	void		setValue(eValue value);
	void		setDefaultValue(eValue value);
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
	std::string 	name;
	eValue 			defaultValue;
	eValue 			value;
};

std::ostream &operator<<(std::ostream &o, Element &c);
