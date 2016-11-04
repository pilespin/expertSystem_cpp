
#pragma once

#include <project.hpp>
#include "Rule.hpp"

class Parse {

public:
	Parse();
	~Parse();
	Parse(Parse const &src);
	Parse &operator=(Parse const &rhs);

	int			getValue() const;
	void		empty();
	void		printRule();
	void		printFact();
	void		printQueries();

	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

	void	openFile(std::string filename);
	void	readFile();
	void	closeFile();
	void	createTree();

private:
	eImplication 	get_eImplicationByName(std::string implies);
	std::string		removeComments(std::string line);
	void			parse(std::string line);

	int 			_val;
	std::ifstream 	file;

	std::list<Rule>			rule;
	std::list<std::string>	fact;
	std::list<std::string>	querie;
};

std::ostream &operator<<(std::ostream &o, Parse &c);
