
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"

// void	Parse::computeMultipleElement() {

// }

void	Parse::forwardChaining() {

	bool oneHasImpliqued = true;

	while (oneHasImpliqued == true)
	{
		oneHasImpliqued = false;
		for (auto it = this->rule.begin(); it != this->rule.end(); it++)
		{	
			int size = it->item.size();

			auto Iitem = it->item.begin();

			this->setMagicTransformUndefinedToFalse();
			if (!it->getExecuted())
			{
				if (size == 1)
				{

					Element	*first = this->getElement(this->getGoodName(*Iitem));
					eValue	one = this->getGoodValue(*Iitem, first->getValue());

					if (one == eValue::True)
					{
						it->setExecuted();
						oneHasImpliqued = true;
						setValueAtElement(it->impliqued, eValue::True);
					}
				}
				else
				{
					eValue	one;
					eValue	two;

					Element	*first = this->getElement(this->getGoodName(*Iitem));
					one = this->getGoodValue(*Iitem, first->getValue());

					while (size--)
					{
						Element *second = nullptr;
						if (size)
						{
							Iitem++;
							second = this->getElement(this->getGoodName(*Iitem));
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
			}
		}
	}
}
