#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <list>
#include "Enum.hpp"

	// 	ALLOWED_CHAR					"\\!?\\s*[A-Za-z]*"
#define REGEX_GET_INITIAL_FACTS			"^\\s*=\\s*(.*)\\s*"
#define REGEX_GET_INITIAL_QUERIES		"^\\s*\\?\\s*(.*)\\s*"
#define REGEX_GET_RULE					"^\\s*(.*?)\\s*(<?=>)\\s*(\\!?\\s*[A-Za-z]*)\\s*$"
#define REGEX_GET_ELEMENT_IN_RULE		"\\s*(\\!?\\s*[A-Za-z]*)\\s*([\\+\\^\\|])\\s*(\\!?\\s*[A-Za-z]*)\\s*"
#define REGEX_GET_ONE_ELEMENT_IN_RULE	"^\\s*(\\!?\\s*[A-Za-z]*)\\s*$"
#define REGEX_GET_FACT					"[a-zA-Z]+"
#define REGEX_GET_QUERIE				"[a-zA-Z]+"
#define REGEX_GET_FACT_SIMPLE			"[a-zA-Z]"
#define REGEX_GET_QUERIE_SIMPLE			"[a-zA-Z]"
