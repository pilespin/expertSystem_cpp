
#include <project.hpp>
#include "Element.hpp"
#include "Parse.hpp"

void	Parse::forwardChaining() {

	// double 				timeStart 		= mylib::utime();
	unsigned long long 	iteration 	= 0;
	unsigned long long 	passage		= 0;
	unsigned long long 	maxPassage	= this->rule.size();

	// bool printBadRule = true;
	// bool error = false;

	while (passage <= maxPassage + 1)
	{
		// if (passage > maxPassage)
			// printBadRule = true;
		passage++;

		for (auto it = this->rule.begin(); it != this->rule.end(); it++)
		{
			iteration++;
			eValue res 	= this->computeRule(&*it);
			if (res == eValue::Undefined)
				continue;
			res 			= getGoodValue(it->impliqued, res);
			eValue oldValue	= this->getElement(it->impliqued)->getValue();

			if (res != oldValue)
			{
				if (passage == maxPassage -1)
				{
					// error = true;
					// std::cout << "Conflict: " << *it << std::endl;
					setValueAtElement(it->impliqued, eValue::Undefined);
				}
				else
					setValueAtElement(it->impliqued, res);
			}
		}
	}

	// std::cout << this->rule.size() << " rules" << std::endl;
	// std::cout << iteration << " iterations" << std::endl;
	// std::cout << (mylib::utime() - timeStart) * 1000 << " ms" << std::endl;

	// if (error)
		// throw Msg("Error some conflict in rule has been detected");	
}
