#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <list>
#include "Enum.hpp"

#define REGEX_GET_RULE				"(.*?)(<?=>)(.*)"
#define REGEX_GET_INITIAL_FACTS		"^=(.*)"
#define REGEX_GET_INITIAL_QUERIES	"^\\?(.*)"
#define REGEX_GET_ELEMENT_IN_RULE	"([A-Za-z]*)\\s*([\\+\\^\\|])\\s*([A-Za-z]*)"
