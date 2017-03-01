#ifndef HYPERCSV_FILEUTILITY_H
#define HYPERCSV_FILEUTILITY_H

#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include <set>
#include <iterator>
#include <unordered_map>
#include <list>

#include "Max.h"

#include "Dataset.h"
#include "Column.h"
#include "ExpressionParser.h"

/// @author Alexander Pinkerton

/** Utility class which allows the reading of csv files and subsequent actions on them.
 *  This class can be used to read a csv file into memory as well as performing a job-list on a file **/
class FileUtility
{

public:
    
    static int columnCount(std::ifstream &filestream);

    static int lineCount(std::ifstream &filestream);

    static std::vector<std::string> getFieldNames(std::ifstream &filestream);

    static std::unordered_map<int, Column> createColumns(std::ifstream &filestream, std::set<int> &&);

    static void printColumns(std::ifstream &filestream, std::set<int> &);

    static Dataset loadDataset(std::ifstream &&filestream);

    static void readAndRunJobs(std::ifstream &, std::list<SinglePassJob *> &);

    static std::vector<std::string> getLineAndSplit(std::ifstream &filestream, char &&);

    template<typename T>
    static void split(const std::string &, char, T);

    static std::vector<std::string> split(const std::string &, char);

};


#endif //HYPERCSV_FILEUTILITY_H
