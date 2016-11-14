
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"

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
		error = false;
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
			}
		}

		if (!error && it->item.size() == 0)
			error = true;

		if (!error && it->optr.size() != 0)
		{
			unsigned int size_optr = 0;
			if (*it->optr.begin() != eLogicOperator::None)
				size_optr = it->optr.size();
			if (it->item.size() - 1 != size_optr)
				error = true;
		}
		if (error)
		{
			std::cerr << "An error has benn detected in rule: " << it->elem << std::endl;
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
