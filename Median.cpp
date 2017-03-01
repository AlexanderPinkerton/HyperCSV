#include "Median.h"

/// @author Alexander Pinkerton

//This Class uses two heaps to find a "running" median which only requires one pass over the data.

Median::Median()
{
	result = 0;
	name = "Median";
}

Median::Median(int colNum)
{
	result = 0;
	name = "Median";
	columnNum = colNum;
}


Median::~Median()
{
}

void Median::update(float next)
{
	addNumber(next, highers, lowers);
	rebalance(highers, lowers);
}

void Median::update(std::vector<std::string>& cells)
{

}

void Median::finish()
{
	result = getMedian(highers, lowers);
}

void Median::addNumber(float & number, std::priority_queue<float, std::vector<float>, Median::minComparator>  & highers, std::priority_queue<float, std::vector<float>>  & lowers)
{
	if (lowers.empty() || number < lowers.top())
	{
		lowers.push(number);
	}
	else
	{
		highers.push(number);
	}
}

void Median::rebalance(std::priority_queue<float, std::vector<float>, Median::minComparator>  & highers, std::priority_queue<float, std::vector<float>>  & lowers)
{
	//Rebalance the heap by moving elements from the larger heap into the smaller.
	bool lowersBigger = lowers.size() > highers.size();
	if (lowersBigger)
	{
		//Move elements from lower to higher if off balance by 2
		if (lowers.size() - highers.size() >= 2)
		{
			highers.push(lowers.top());
			lowers.pop();
		}
	}
	else
	{
		//Move elements from higher to lower if off balance by 2
		if (highers.size() - lowers.size() >= 2)
		{
			lowers.push(highers.top());
			highers.pop();
		}
	}

}

float Median::getMedian(std::priority_queue<float, std::vector<float>, Median::minComparator>  & highers, std::priority_queue<float, std::vector<float>>  & lowers)
{
	bool lowersBigger = lowers.size() > highers.size();
	if (lowersBigger)
	{
        //If there is an even number of entries, get the average
		if (lowers.size() == highers.size())
		{
			return (float)(lowers.top() + highers.top()) / 2;
		}
		else
		{
			return lowers.top();
		}
	}
	else
	{
        //If there is an even number of entries, get the average
		if (highers.size() == lowers.size())
		{
			return (float)(highers.top() + lowers.top()) / 2;
		}
		else
		{
			return highers.top();
		}
	}

}
