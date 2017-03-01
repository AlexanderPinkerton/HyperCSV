#pragma once

#include "SinglePassJob.h"
#include <vector>


class Min : public SinglePassJob
{
public:
	Min();
	Min(int columnNum);
	~Min();

	void update(float value);
	void update(std::vector<std::string> & cells);
	void finish();

};

