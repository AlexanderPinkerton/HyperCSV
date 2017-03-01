#pragma once

#include "SinglePassJob.h"
#include <vector>
#include <stack>

#include "FileUtility.h"

class Expression : public SinglePassJob
{
public:
	Expression();
	Expression(std::string & postfix);
	Expression(std::string && postfix);
	~Expression();

	std::string postfix;

	std::stack<float> operandStack;

	void update(float value);
	void update(std::vector<std::string> & cells);
	void finish();

};

