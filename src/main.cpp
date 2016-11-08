
#include <project.hpp>
#include "Parse.hpp"
#include "Branch.hpp"

int main()
{
	try
	{
	Parse p = Parse();

	// std::cout << "regex: " << REGEX_GET_ONE_ELEMENT_IN_RULE << std::endl;

	p.readFile("rule");
	p.createTree();

	p.printRule();
	p.printFact();
	p.printQueries();



	// Branch *a = new Branch("A", eNegative::False, eValue::True);

	// Branch *c = new Branch("C", eNegative::False, eValue::True);
	// Branch *d = new Branch("D", eNegative::False, eValue::True);

	// Branch *b = new Branch("B", eNegative::False, eLogicOperator::Ou,
	// 	eValue::Undefined, eImplication::Simple, c, d);

	// Branch *x = new Branch("X", eNegative::False, eLogicOperator::Et,
	// 	eValue::Undefined, eImplication::Simple, a, b);



	// b->print();
	// x->print();
	// x->calcResult();
	// std::cout << "----------------------------------" << std::endl;
	// b->print();
	// x->print();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
