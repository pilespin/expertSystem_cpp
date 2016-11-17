
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
	void		init();
	void 		setMultipleCharInElement();
	void 		forwardChaining();
	void 		backwardChaining();

	////////// PRINT //////////
	void	printRule();
	void	printFact();
	void	printQueries();
	void	printTrueElement();
	void	printAllElement();

	////////// IO //////////
	void	openFile(std::string filename);
	void	readFile(std::string filename = "");

	///////////////////////////// EXCEPTION ///////////////////////////////////
	class Msg : public std::exception {
	public:
		Msg(std::string str) 						{	this->line += str;	}
		virtual const char *what() const throw() 	{ return (this->line.c_str()); }
	private:
		std::string line;
	};

private:
	
	void			createMap();
	void 			insertIntoMap(std::string tmp);
	void			setInitialFact();
	Element 		*getElement(std::string elem);
	void			setValueAtElement(std::string elem, eValue val);

	void			calcRule();
	void			getFact();
	void			getQuerie();
	bool			createRule(std::string line, size_t linePos);
	eImplication 	get_eImplicationByName(std::string implies);
	std::string		removeComments(std::string line);

	eValue			compute(eValue one, eLogicOperator optr, eValue two);
	bool 			getMultipleCharInElement();
	bool			getMagicTransformUndefinedToFalse();
	void			setMagicTransformUndefinedToFalse();
	bool			checkIsNegative(std::string elem);
	std::string		getGoodName(std::string elem);
	eValue			getGoodValue(std::string elem, eValue val);

	eValue			computeRule(Rule *rule);
	eValue			computeOneElement(Rule *rule);
	eValue			computeMultipleElement(Rule *rule);
	
	void			empty();
	void			closeFile();

	////////// VAR //////////
	int 			_val;
	bool 			multipleCharInElement;
	bool 			transformUndefinedToFalse;
	bool 			oneHasImpliqued;
	std::ifstream 	file;

	std::map<std::string, Element>	mapElem;

	std::list<Rule>			rule;
	std::list<std::string>	fact;
	std::list<std::string>	querie;
	std::list<std::string>	allfact;
	std::list<std::string>	allquerie;
};

std::ostream &operator<<(std::ostream &o, Parse &c);
