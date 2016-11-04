
#include <project.hpp>
#include "Branch.hpp"
#include "Parse.hpp"

Parse::Parse() 						{	this->_val = 0;	}

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
int		Parse::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////

static std::string trim(std::string str)
{
	int st;
	int end;

	st = str.find_first_not_of(" 	");
	end = str.find_last_not_of(" 	");

	if ((end > -1 && st > -1))
		return (str.substr(st, (end - st) + 1));
	else
		return ("");
}

void	Parse::openFile(std::string filename) {
	this->file.open(filename);
	if (!this->file.is_open())
	{
		std::cout << "Unable to open file: " << filename << std::endl;
	}
}

void	Parse::closeFile() {
	if (this->file.is_open())
		this->file.close();
}

std::string	Parse::removeComments(std::string line) {
	if (line.find_first_of("#") != std::string::npos)
		line = line.substr(0, line.find_first_of("#"));
	line = trim(line);
	return (line);
}

eImplication Parse::get_eImplicationByName(std::string implies) {

	if (!implies.compare("=>"))
		return (eImplication::Simple);	
	else if (!implies.compare("<=>"))
		return (eImplication::Double);	
	else 
		throw Msg("Error when converting implies from string");
}

void	Parse::parse(std::string line) {
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
		std::cout << "Syntax error" << std::endl;
}

void	Parse::createTree() {
	std::smatch res;

	for (auto it = this->rule.begin() ; it != this->rule.end() ; ++it)
	{
		// if (std::regex_search(it->elem, res, std::regex(REGEX_GET_ELEMENT_IN_RULE)))
		// {
		// 	std::cout << "-------------------------" << std::endl;

		// 	std::cout << res[1] << std::endl;
		// 	std::cout << res[2] << std::endl;
		// 	std::cout << res[3] << std::endl;
	


		// 	std::cout << "-------------------------" << std::endl;

		// }
		// else 
		// 	throw Msg("Error when retrieving element in rule");

		std::cout << "elem:      " << it->elem << std::endl;
		std::cout << "implies:   " << static_cast<int>(it->implies) << std::endl;
		std::cout << "impliqued: " << it->impliqued << std::endl;
		std::cout << std::endl;

		Branch *a = new Branch("A", eNegative::False, eValue::Undefined);
		Branch *b = new Branch("B", eNegative::False, eValue::Undefined);

		Branch *x = new Branch(it->impliqued, eNegative::False, eLogicOperator::Et,
			eValue::Undefined, it->implies, a, b);

		x->print();

	}

}

void	Parse::printRule() {

	std::cout << "rule: " << std::endl;
	for (auto it = this->rule.begin() ; it != this->rule.end() ; ++it)
	{
		std::cout << "elem:      " << it->elem << std::endl;
		std::cout << "implies:   " << static_cast<int>(it->implies) << std::endl;
		std::cout << "impliqued: " << it->impliqued << std::endl;
		std::cout << std::endl;
	}
}

void	Parse::printFact() {

	for (auto it = this->fact.begin() ; it != this->fact.end() ; ++it)
	{
		std::cout << "fact: " << *it << std::endl;
	}
}

void	Parse::printQueries() {

	for (auto it = this->querie.begin() ; it != this->querie.end() ; ++it)
	{
		std::cout << "querie: " << *it << std::endl;
	}
}

void	Parse::readFile() {

	std::string line;

	if (this->file.is_open())
	{
		while (getline(this->file, line))
		{
			line = removeComments(line);
			if (line.length() > 0)
			{
				parse(line);
			}
		}
		closeFile();
	}
	else
		std::cerr << "Please call openFile before" << std::endl;
}

void	Parse::empty() {

}
