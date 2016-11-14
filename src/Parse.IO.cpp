
#include <project.hpp>
#include "Element.hpp"
#include "Branch.hpp"
#include "Parse.hpp"
#include "mylib.hpp"

////////////////////////////////////// IO /////////////////////////////////////

void	Parse::openFile(std::string filename) {

	this->file.open(filename);
	if (!this->file.is_open())
	{
		throw Msg("Error: Unable to open file " + filename);
	}
}

void	Parse::closeFile() {
	if (this->file.is_open())
		this->file.close();
}

void	Parse::readFile(std::string filename) {

	if (filename.length())
		openFile(filename);

	std::string line;
	size_t		linePos = 0;
	bool		error = false;

	if (this->file.is_open())
	{
		while (getline(this->file, line))
		{
			++linePos;
			line = removeComments(line);
			if (line.length())
			{
				if (!createRule(line, linePos))
					error = true;
			}
		}
		closeFile();
	}
	else
		throw Msg("Error: Unable to open file " + filename);

	if (error)
		throw Msg("Some error has been detected");
}
