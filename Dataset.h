#pragma once

#include <unordered_map>

#include "Column.h"


class Dataset
{
public:
	Dataset(std::unordered_map<int, Column> columns);
	~Dataset();

	int columnCount;
	int rowCount;

	std::unordered_map<int, Column> data;
	std::unordered_map<std::string, int> fieldIndices;
	std::vector<std::string> fieldNames;

	std::vector<float> getRow(int & rowIndex);
	std::vector<float> getRow(int && rowIndex);

	void setFieldIndices(std::vector<std::string> & fieldNames);

};

