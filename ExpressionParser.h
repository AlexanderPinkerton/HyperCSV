#pragma once

#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <cmath>

 


#include "FileUtility.h"

#include <iostream>

/// @author Alexander Pinkerton

class ExpressionParser
{
public:

	enum Operator { EQUALS=0, LEFTPARENTHESIS=0, RIGHTPARENTHESIS=0, ADD=1, SUBTRACT=1, MULTIPLY=2, DIVIDE=2, POWER=3 };

	ExpressionParser();
	~ExpressionParser();

	static std::string generateRPN(std::string & infix);
	static float evaluateExpression(std::vector<std::string>& cells, std::string & postfix);

private:

	static std::unordered_map<std::string, Operator> ops;
	static bool isHigherPrec(std::string & op, std::string  & sub);

};

