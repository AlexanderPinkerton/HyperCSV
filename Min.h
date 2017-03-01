#pragma once

#include "SinglePassJob.h"
#include <vector>

/// @author Alexander Pinkerton

/** This class is a SinglePassJob which will calculate the minimum of all of the values sent to it via update once its finish method is called. **/
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

