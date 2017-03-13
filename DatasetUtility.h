#pragma once

#include "Dataset.h"
#include <iostream>
#include <string>
#include <set>



/// @author Alexander Pinkerton

/** Utility class which provides static functions to manipulate a Dataset **/
class DatasetUtility
{
public:
	DatasetUtility();
	~DatasetUtility();

	static std::vector<std::string> GetJoinFields(Dataset & set1, Dataset & set2, std::string & joinField);

	static void PrintRow(std::vector<float> & row);
	static void PrintRow(std::unordered_map<std::string, float> & row, std::vector<std::string> & fields);
	static void PrintJoinFields(std::vector<std::string> & joinFields);
	static void InnerJoinAndPrint(Dataset & set1, Dataset & set2, std::string & joinField);
	static void OuterJoinAndPrint(Dataset & set1, Dataset & set2, std::string & joinField);


};

