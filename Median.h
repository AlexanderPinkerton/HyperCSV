#pragma once

#include "SinglePassJob.h"
#include <vector>
#include <queue>
#include <iostream>


/// @author Alexander Pinkerton

/** This class is a SinglePassJob which will calculate the median of all of the values sent to it via update once its finish method is called. **/
class Median : public SinglePassJob
{


public:
	Median();
	Median(int columnNum);
	~Median();

	//Custom comparator to implement max heap.
	struct minComparator {
		bool operator()(float i, float j) {
			return i > j;
		}
	};

	//Two stacks to hold the running values
	std::priority_queue<float, std::vector<float>, minComparator> highers;
	std::priority_queue<float, std::vector<float>> lowers;


	void addNumber(float & number, std::priority_queue<float, std::vector<float>, Median::minComparator> & highers, std::priority_queue<float, std::vector<float>> & lowers);
	void rebalance(std::priority_queue<float, std::vector<float>, Median::minComparator> & highers, std::priority_queue<float, std::vector<float>> & lowers);
	float getMedian(std::priority_queue<float, std::vector<float>, Median::minComparator> & highers, std::priority_queue<float, std::vector<float>> & lowers);


	//Overrides
	void update(float value);
	void update(std::vector<std::string> & cells);
	void finish();

};

