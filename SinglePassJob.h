#pragma once

#include <string>
#include <vector>

/// @author Alexander Pinkerton

/** This class is an Abstract Class which contains update and finish methods along with a result value
 *  The update method should be called to update the result value
 *  The finish method should be called when the job result is needed **/
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

