#pragma once

#include "SinglePassJob.h"
#include <vector>

/** This class is a SinglePassJob which will calculate the average of all of the values sent to it via update once its finish method is called. **/
class Average : public SinglePassJob
{
public:
	Average();
	Average(int columnNum);
	~Average();

	int numElements = 0;

	void update(float value);
	void update(std::vector<std::string> & cells);
	void finish();

};

