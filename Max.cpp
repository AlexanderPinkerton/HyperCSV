#include "Max.h"



Max::Max()
{
	result = -9999999.0f;
	name = "Maximum";
}

//TODO: Use Numeric limits instead of static values.

Max::Max(int colNum)
{
	result = -9999999.0f;
	name = "Maximum";
	columnNum = colNum;
}


Max::~Max()
{
}

void Max::update(float next)
{
	if (next > result) {
		result = next;
	}
}

void Max::update(std::vector<std::string>& cells)
{

}

void Max::finish()
{

}


