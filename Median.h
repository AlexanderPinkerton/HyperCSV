#pragma once

#include "SinglePassJob.h"
#include <vector>
#include <queue>
#include <iostream>

class Median : public SinglePassJob
{


public:
	Median();
	Median(int columnNum);
	~Median();

	struct minComparator {
		bool operator()(float i, float j) {
			return i > j;
		}
	};

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

