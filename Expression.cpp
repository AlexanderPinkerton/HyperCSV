#include "Expression.h"



Expression::Expression()
{
	name = "Expression";
}

Expression::Expression(std::string & rpn)
{
	name = "Expression";
	postfix = rpn;
}

Expression::Expression(std::string && rpn)
{
	name = "Expression";
	postfix = rpn;
}


Expression::~Expression()
{
}

void Expression::update(float next)
{

}

void Expression::update(std::vector<std::string>& cells)
{
	result = ExpressionParser::evaluateExpression(cells, postfix);
}

void Expression::finish()
{

}


