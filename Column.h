#pragma once

#include <vector>
#include <string>

/// @author Alexander Pinkerton

class Column
{
public:
	Column();
	Column(std::string &);
	~Column();

	int length;
	std::string name;
	std::vector<float> entries;

	void addEntry(const float &);

	float& operator[] (int &&);
	float& operator[] (int &);




};

