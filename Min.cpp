#include "Min.h"


Min::Min()
{
	result = 99999999.0f;
	name = "Minimum";
}

//TODO: Use Numeric limits instead of static values.

Min::Min(int colNum)
{
	result = 99999999.0f;
	name = "Minimum";
	columnNum = colNum;
}


Min::~Min()
{
}

void Min::update(float next)
{
	if (next < result) {
		result = next;
	}
}

void Min::update(std::vector<std::string>& cells)
{

}

void Min::finish()
{

}


