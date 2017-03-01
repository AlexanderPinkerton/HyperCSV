#include "Average.h"

Average::Average()
{
	result = 0;
	name = "Average";
}

Average::Average(int colNum)
{
	result = 0;
	name = "Average";
	columnNum = colNum;
}


Average::~Average()
{
}

void Average::update(float next)
{
	result += next;
	numElements++;
}

void Average::update(std::vector<std::string>& cells)
{

}

void Average::finish()
{
	result = result / numElements;
}


