#pragma once

#include <string>
#include <vector>


class SinglePassJob
{
public:
	SinglePassJob();
	virtual ~SinglePassJob();

	float result;
	bool isComplete;

	int columnNum = -1;

	std::string name;

	//Pure virtual functions
	virtual void update(float value)=0;
	virtual void update(std::vector<std::string> & cells) = 0;
	//This method is to be run when the job is done.
	virtual void finish() = 0;

};

