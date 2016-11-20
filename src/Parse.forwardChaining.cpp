
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"

void	Parse::forwardChaining() {

	double 				timeStart = mylib::utime();
	unsigned long long 	iteration = 0;
	
	oneHasImpliqued = true;
	// this->setMagicTransformUndefinedToFalse();

	while (oneHasImpliqued == true)
	{
		oneHasImpliqued = false;
		for (auto it = this->rule.begin(); it != this->rule.end(); it++)
		{
			iteration++;
			eValue res 		= this->computeRule(&*it);
			eValue oldValue	= this->getElement(it->impliqued)->getValue();

			if (res != oldValue)
			{
				oneHasImpliqued = true;
				setValueAtElement(it->impliqued, res);
			}
		}
	}
	double timeEnd = mylib::utime();

	std::cout << this->rule.size() << " rules" << std::endl;
	std::cout << iteration << " iterations" << std::endl;
	std::cout << (timeEnd - timeStart) * 1000 << " ms" << std::endl;
}

eValue	Parse::computeRule(Rule *rule) {

	eValue	res = eValue::Undefined;

	if (rule->item.size() == 1)
	{
		res = this->computeOneElement(rule);
	}
	else
	{
		res = this->computeMultipleElement(rule);
	}
	return (res);
}

eValue	Parse::computeOneElement(Rule *rule) {

	auto Iitem = rule->item.begin();

	Element	*first = this->getElement(*Iitem);
	eValue	one = this->getGoodValue(*Iitem, first->getValue());

	// if (one == eValue::True)
	// {
		// rule->setExecuted();
		// oneHasImpliqued = true;
	// }
	return (one);
}

eValue	Parse::computeMultipleElement(Rule *rule) {

	int 	size = rule->item.size();
	auto 	Iitem = rule->item.begin();
	eValue	one;
	eValue	two;
	eValue	res = eValue::Undefined;

	Element	*first = this->getElement(*Iitem);
	one = this->getGoodValue(*Iitem, first->getValue());

	auto Ioptr = rule->optr.begin();
	while (size--)
	{
		Element *second = nullptr;
		if (size)
		{
			Iitem++;
			second = this->getElement(*Iitem);
			two = this->getGoodValue(*Iitem, second->getValue());
		}
		if (first && second)
		{
			res = compute(one, *Ioptr, two);
				// std::cout << "one: " << Enum::getValue(one) << std::endl;
				// std::cout << "opt: " << Enum::getLogicOperator(*Ioptr) << std::endl;
				// std::cout << "two: " << Enum::getValue(two) << std::endl;
				// std::cout << "res: " << Enum::getValue(res) << std::endl;

			if (size == 1 && res == eValue::True)
			{
				// rule->setExecuted();
				// oneHasImpliqued = true;
				break;
			}
			else
				one = res;

			Ioptr++;
		}
	}
	return (res);
}
