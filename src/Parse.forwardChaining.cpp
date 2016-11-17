
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"

void	Parse::forwardChaining() {

	eValue res;
	oneHasImpliqued = true;

	while (oneHasImpliqued == true)
	{
		oneHasImpliqued = false;
		for (auto it = this->rule.begin(); it != this->rule.end(); it++)
		{
			this->setMagicTransformUndefinedToFalse();
			
			if (!it->getExecuted())
			{
				res = computeRule(&*it);

				if (res == eValue::True)
				{
					it->setExecuted();
					setValueAtElement(it->impliqued, res);
				}
			}
		}
	}
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

	if (one == eValue::True)
	{
		rule->setExecuted();
		oneHasImpliqued = true;
	}
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

	while (size--)
	{
		Element *second = nullptr;
		if (size)
		{
			Iitem++;
			second = this->getElement(*Iitem);
			two = this->getGoodValue(*Iitem, second->getValue());
		}
		auto Ioptr = rule->optr.begin();
		if (first && second)
		{
			res = compute(one, *Ioptr, two);

			if (size == 1 && res == eValue::True)
			{
				rule->setExecuted();
				oneHasImpliqued = true;
			}
			else
				one = res;

			Ioptr++;
		}
	}
	return (res);
}
