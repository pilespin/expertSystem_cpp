
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"

void	Parse::forwardChaining() {

	oneHasImpliqued = true;

	while (oneHasImpliqued == true)
	{
		oneHasImpliqued = false;
		for (auto it = this->rule.begin(); it != this->rule.end(); it++)
		{	
			this->setMagicTransformUndefinedToFalse();
			
			if (!it->getExecuted())
			{
				if (it->item.size() == 1)
				{
					this->computeOneElement(it);
				}
				else
				{
					this->computeMultipleElement(it);
				}
			}
		}
	}
}

void	Parse::computeOneElement(auto it) {

	auto Iitem = it->item.begin();

	Element	*first = this->getElement(*Iitem);
	eValue	one = this->getGoodValue(*Iitem, first->getValue());

	if (one == eValue::True)
	{
		it->setExecuted();
		oneHasImpliqued = true;
		setValueAtElement(it->impliqued, eValue::True);
	}
}

void	Parse::computeMultipleElement(auto it) {

	int 	size = it->item.size();
	auto 	Iitem = it->item.begin();
	eValue	one;
	eValue	two;

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
		auto Ioptr = it->optr.begin();
		if (first && second)
		{
			eValue res = compute(one, *Ioptr, two);

			if (size == 1 && res == eValue::True)
			{
				it->setExecuted();
				oneHasImpliqued = true;
				setValueAtElement(it->impliqued, res);
			}
			else
				one = res;

			Ioptr++;
		}
	}
}
