#pragma once

#include "SinglePassJob.h"
#include <vector>


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

