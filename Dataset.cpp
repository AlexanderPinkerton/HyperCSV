#include "Dataset.h"



Dataset::Dataset(std::unordered_map<int, Column> columns)
:data(columns)
{
	columnCount = data.size();
	rowCount = data[0].entries.size();
}

Dataset::~Dataset()
{
}

std::vector<float> Dataset::getRow(int & rowIndex)
{
	std::vector<float> rowVector;
	for (int i = 0; i < columnCount; i++)
	{
		//Add each column to the row vector.
		rowVector.push_back(data[i][rowIndex]);
	}

	return rowVector;
}

std::vector<float> Dataset::getRow(int && rowIndex)
{
	std::vector<float> rowVector;
	for (int i = 0; i < columnCount; i++)
	{
		//Add each column to the row vector.
		rowVector.push_back(data[i][rowIndex]);
	}

	return rowVector;
}

void Dataset::setFieldIndices(std::vector<std::string> & fields)
{
	fieldNames = fields;
	for (unsigned int i = 0; i < fields.size(); i++) {
		fieldIndices[fields[i]] = i;
	}
}
