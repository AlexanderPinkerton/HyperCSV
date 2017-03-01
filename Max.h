#pragma once

#include "SinglePassJob.h"
#include <vector>


class Max : public SinglePassJob
{
public:
	Max();
	Max(int columnNum);
	~Max();

	void update(float value);
	void update(std::vector<std::string> & cells);
	void finish();

};

