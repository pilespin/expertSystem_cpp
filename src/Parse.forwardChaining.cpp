
#include <project.hpp>
#include "Element.hpp"
#include "Parse.hpp"

void	Parse::forwardChaining() {

	// double 				timeStart = mylib::utime();
	// unsigned long long 	iteration = 0;
	
	oneHasImpliqued = true;
	// this->setMagicTransformUndefinedToFalse();

	while (oneHasImpliqued == true)
	{
		oneHasImpliqued = false;
		for (auto it = this->rule.begin(); it != this->rule.end(); it++)
		{
			// iteration++;
			eValue res 		= getGoodValue(it->impliqued, this->computeRule(&*it));
			eValue oldValue	= this->getElement(it->impliqued)->getValue();

			if (res != oldValue)
			{
				oneHasImpliqued = true;
				setValueAtElement(it->impliqued, res);
				// setValueAtElement(it->impliqued, getGoodValue(it->impliqued, res));
			}
		}
	}
	// double timeEnd = mylib::utime();

	// std::cout << this->rule.size() << " rules" << std::endl;
	// std::cout << iteration << " iterations" << std::endl;
	// std::cout << (timeEnd - timeStart) * 1000 << " ms" << std::endl;
}
