
#include <project.hpp>
#include "Element.hpp"
#include "Parse.hpp"

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
