
#pragma once

#include <project.hpp>
#include "Element.hpp"
#include "Rule.hpp"

class Parse {

public:
	Parse();
	~Parse();
	Parse(Parse const &src);
	Parse &operator=(Parse const &rhs);

	int			getValue() const;
	bool 		getMultipleCharInElement();
	void 		setMultipleCharInElement();

	void		empty();
	void		printRule();
	void		printFact();
	void		printQueries();
	void		printElement();
	void 		forwardChaining();
	void		getFact();
	void		getQuerie();



	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

	void	openFile(std::string filename);
	void	readFile(std::string filename = "");
	void	closeFile();
	void	calcRule();
	void	createMap();


private:
	void 			insertIntoMap(std::string tmp);
	eImplication 	get_eImplicationByName(std::string implies);
	std::string		removeComments(std::string line);
	bool			createRule(std::string line, size_t linePos);

	int 			_val;
	bool 			multipleCharInElement;
	std::ifstream 	file;

	std::map<std::string, Element>	mapElem;

	std::list<Rule>			rule;
	std::list<std::string>	fact;
	std::list<std::string>	querie;
	std::list<std::string>	allfact;
	std::list<std::string>	allquerie;
};

std::ostream &operator<<(std::ostream &o, Parse &c);
