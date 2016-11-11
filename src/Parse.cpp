
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"
#include "mylib.hpp"

Parse::Parse() 						{	
	this->_val = 0;
	this->multipleCharInElement = false;
}

Parse::~Parse()						{}

Parse::Parse(Parse const &src)	{	
	this->_val = src._val;
}

Parse	&Parse::operator=(Parse const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Parse &c) {
	o << "Parse: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Parse::getValue() const					{	return (this->_val);					}
bool	Parse::getMultipleCharInElement()		{	return (this->multipleCharInElement);	}
void	Parse::setMultipleCharInElement() 		{	this->multipleCharInElement = true;		}
///////////////////////////////////////////////////////////////////////////////

void	Parse::getFact() {

	if (this->getMultipleCharInElement())
	{
		this->allfact = mylib::split(*this->fact.begin());
	}
	else
	{
		std::string tmp;
		std::string str = *this->fact.begin();
		for (auto it = str.begin(); it != str.end(); it++) {
			tmp = *it;
			tmp = mylib::trim(tmp);
			if (tmp.length())
				this->allfact.push_back(tmp);
		}
	}
}

void	Parse::getQuerie() {

	if (this->getMultipleCharInElement())
	{
		this->allquerie = mylib::split(*this->querie.begin());
	}
	else
	{
		std::string tmp;
		std::string str = *this->querie.begin();
		for (auto it = str.begin(); it != str.end(); it++) {
			tmp = *it;
			tmp = mylib::trim(tmp);
			if (tmp.length())
				this->allquerie.push_back(tmp);
		}
	}
}

std::string		Parse::removeComments(std::string line) {
	if (line.find_first_of("#") != std::string::npos)
		line = line.substr(0, line.find_first_of("#"));
	line = mylib::trim(line);
	return (line);
}

eImplication 	Parse::get_eImplicationByName(std::string implies) {

	if (!implies.compare("=>"))
		return (eImplication::Simple);	
	else if (!implies.compare("<=>"))
		return (eImplication::Double);	
	else 
		throw Msg("Error when converting implies from string");
}

bool	Parse::createRule(std::string line, size_t linePos) {
	std::smatch res;

	if (std::regex_search(line, res, std::regex(REGEX_GET_RULE)))
	{
		this->rule.push_back(Rule(res[1].str(), get_eImplicationByName(res[2].str()), res[3].str()));
	}
	else if (std::regex_search(line, res, std::regex(REGEX_GET_INITIAL_FACTS)))
	{
		this->fact.push_back(res[1].str());
	}
	else if (std::regex_search(line, res, std::regex(REGEX_GET_INITIAL_QUERIES)))
	{
		this->querie.push_back(res[1].str());
	}
	else
	{
		std::cerr << "Syntax error line " << linePos << std::endl;
		return (false);
	}
	return (true);
}

void	Parse::calcRule() {

	std::smatch res;
	bool		error = false;

	std::regex r(REGEX_GET_ELEMENT_IN_RULE);
	for (auto it = this->rule.begin() ; it != this->rule.end() ; ++it)
	{
		if (std::regex_search(it->elem, res, r))
		{
			for(std::sregex_iterator i = std::sregex_iterator(it->elem.begin(), it->elem.end(), r);
				i != std::sregex_iterator();
				++i )
			{
				res = *i;
				if (res[1].length())
					it->item.push_back(res[1]);
				if (res[2].length())
					it->optr.push_back(Enum::getLogicOperator(res[2]));
				if (res[3].length())
					it->item.push_back(res[3]);
			}
		}
		else
		{
			if (std::regex_search(it->elem, res, std::regex(REGEX_GET_ONE_ELEMENT_IN_RULE)))
			{
				if (it->elem.length())
				{
					it->item.push_back(it->elem);
					it->optr.push_back(eLogicOperator::None);
				}
			}
			else
			{
				error = true;
				std::cerr << "An error has benn detected in rule: " << it->elem << std::endl;
			}
		}

			// for (auto it1 = it->item.begin(); it1 != it->item.end(); ++it1)
			// {
			// 	std::cout << "item:      " << *it1 << std::endl;
			// }

			// for (auto it2 = it->optr.begin(); it2 != it->optr.end(); ++it2)
			// {
			// 	std::cout << "optr:      " << Enum::getLogicOperator(*it2) << std::endl;
			// }

			// auto itm = it->item.begin();
			// auto op = it->optr.begin();
			// (void)op;
			// (void)itm;

			// std::string currentHead;

			// currentHead = it->impliqued;
			// while (itm != it->item.end())
			// {
			// 	std::cout << "created: " << '"' << *itm << '"' << std::endl;
			// 	Branch *tmp1 = new Branch(*itm, eNegative::False, eValue::Undefined);
			// 	itm++;

			// 	std::cout << "created: " << '"' << *itm << '"' << std::endl;
			// 	Branch *tmp2 = new Branch(*itm, eNegative::False, eValue::Undefined);
			// 	// itm++;

			// 	std::cout << "createbranch: " << '"' << currentHead << '"' << std::endl;
			// 	Branch *br = new Branch(currentHead, eNegative::False, *op,
			// 		eValue::Undefined, it->implies, tmp1, tmp2);

			// 	currentHead = *itm;
			// 	itm++;

			// 	br->print();
			// 	op++;


			// 	(void)br;
			// 	(void)tmp1;
			// 	(void)tmp2;

			// }

			// std::cout << "elem:      " << it->elem << std::endl;
			// std::cout << "implies:   " << static_cast<int>(it->implies) << std::endl;
			// std::cout << "impliqued: " << it->impliqued << std::endl;
			// std::cout << std::endl;

			// Branch *a = new Branch("A", eNegative::False, eValue::Undefined);
			// Branch *b = new Branch("B", eNegative::False, eValue::Undefined);

			// Branch *x = new Branch(it->impliqued, eNegative::False, eLogicOperator::Et,
			// 	eValue::Undefined, it->implies, a, b);

			// x->print();

		// }
	}
	if (error)
		throw Msg("Some error has been detected");
}

void 	Parse::insertIntoMap(std::string tmp) {
	if ((tmp).find_first_of("!") == 0)
		tmp.erase(0, 1);
	this->mapElem[tmp] = Element(tmp, eValue::Undefined);
}

void	Parse::createMap() {

	std::string tmp;

	for (auto it = this->rule.begin() ; it != this->rule.end() ; it++) {
		for (auto it1 = it->item.begin() ; it1 != it->item.end() ; it1++) {
			insertIntoMap(*it1);
		}
		insertIntoMap(it->impliqued);
	}
}

void	Parse::forwardChaining() {

	for(auto it = this->mapElem.begin(); it != this->mapElem.end(); it++)
	{	
		// std::cout << it->second;
	}
}

//////////////////////////////////  PRINT  ////////////////////////////////////

void	Parse::printElement() {

	for(auto it = this->mapElem.begin(); it != this->mapElem.end(); it++)
	{	
		std::cout << it->second;
	}
}

void	Parse::printRule() {

	std::cout << "rule: " << std::endl;
	for (auto it = this->rule.begin() ; it != this->rule.end() ; it++)
	{
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "elem:      " << '"' << it->elem << '"' << std::endl;
		std::cout << "implies:   " << '"' << Enum::getImplication(it->implies) << '"' << std::endl;
		std::cout << "impliqued: " << '"' << it->impliqued << '"' << std::endl;
		std::cout << std::endl;

		for (auto it1 = it->item.begin(); it1 != it->item.end(); it1++)
		{
			std::cout << "item:      " << '"' << *it1 << '"' << std::endl;
		}
		for (auto it1 = it->optr.begin(); it1 != it->optr.end(); it1++)
		{
			std::cout << "optr:      " << Enum::getLogicOperator(*it1) << std::endl;
		}
		std::cout << "-----------------------------------" << std::endl;
	}
}

void	Parse::printFact() {

	for (auto it = this->fact.begin() ; it != this->fact.end() ; ++it)
	{
		std::cout << "fact: " << '"' << *it << '"' << std::endl;
	}

	for (auto it = this->allfact.begin(); it != this->allfact.end(); it++) {
		std::cout << '"' << *it << '"'  <<std::endl;
	}
}

void	Parse::printQueries() {

	for (auto it = this->querie.begin() ; it != this->querie.end() ; ++it)
	{
		std::cout << "querie: " << '"' << *it << '"' <<  std::endl;
	}
	for (auto it = this->allquerie.begin(); it != this->allquerie.end(); it++) {
		std::cout << '"' << *it << '"'  <<std::endl;
	}
}

////////////////////////////////////// IO /////////////////////////////////////

void	Parse::openFile(std::string filename) {

	this->file.open(filename);
	if (!this->file.is_open())
	{
		throw Msg("Error: Unable to open file " + filename);
	}
}

void	Parse::closeFile() {
	if (this->file.is_open())
		this->file.close();
}

void	Parse::readFile(std::string filename) {

	if (filename.length())
		openFile(filename);

	std::string line;
	size_t		linePos = 0;
	bool		error = false;

	if (this->file.is_open())
	{
		while (getline(this->file, line))
		{
			++linePos;
			line = removeComments(line);
			if (line.length())
			{
				if (!createRule(line, linePos))
					error = true;
			}
		}
		closeFile();
	}
	else
		throw Msg("Error: Unable to open file " + filename);

	if (error)
		throw Msg("Some error has been detected");
}

///////////////////////////////////// ELSE ////////////////////////////////////

void	Parse::empty() {

}
