// HyperCSV.cpp : Defines the entry point for the console application.
//

#include<memory>

#include "FileUtility.h"
#include "ArgumentParser.h"
#include "Min.h"
#include "Median.h"
#include "Average.h"
#include "DatasetUtility.h"
#include "Expression.h"

/// @author Alexander Pinkerton

int main(int argc, char **argv)
{
    ArgumentParser input(argc, argv);

    //Handle all operations that work with a single file.
    if (input.cmdOptionExists("-f"))
    {
        std::string &filename = input.getCmdOption("-f");

        if (!filename.empty()) {
            //Create a list to hold all the jobs to be run while reading the file. Must use * since abstract
            std::list<SinglePassJob*> jobList;

            std::ifstream inputFile(filename);

            int columnCount = FileUtility::columnCount(inputFile);

            //TODO Allows the passing of column intervals by indicies.
            // Handle select column flag----------------------------------------------------------------------------
            if (input.cmdOptionExists("-select"))
            {
                std::vector<std::string> columnIndices = FileUtility::split(input.getCmdOption("-select"), ',');
                std::set<int> colSet;
                for (auto i = columnIndices.begin(); i < columnIndices.end(); i++) {

                    int columnIndex = 0;
                    try {
                        columnIndex = std::stoi(*i);
                    }
                    catch (std::invalid_argument& e) {
                        // if no conversion could be performed
                    }
                    catch (std::out_of_range& e) {

                    }

                    if (columnIndex > 0 && columnIndex < columnCount)
                    {
                        colSet.insert(columnIndex);
                    }

                }
                FileUtility::printColumns(inputFile, colSet);
            }


            // Handle the expression flag----------------------------------------------------------------------------
            if (input.cmdOptionExists("-e"))
            {
                std::string & infixExpression = input.getCmdOption("-e");
                jobList.push_back(new Expression(ExpressionParser::generateRPN(infixExpression)));
            }

            // Handle the info flag---------------------------------------------------------------------------------
            if (input.cmdOptionExists("-info"))
            {
                //Print the fieldnames of the file.
                std::vector<std::string> fieldnames = FileUtility::getFieldNames(inputFile);
                for (auto it = fieldnames.begin(); it < fieldnames.end(); it++) {
                    std::cout << *it << "\t";
                }
                std::cout << std::endl;
                std::cout << "Columns : " << FileUtility::columnCount(inputFile) << std::endl;
                std::cout << "Rows : " << FileUtility::lineCount(inputFile) << std::endl;
            }


            // Handle the statistics flag----------------------------------------------------------------------------
            if (input.cmdOptionExists("-s"))
            {
                const std::string &statistic = input.getCmdOption("-s");

                if (input.cmdOptionExists("-col"))
                {
                    const std::string &column = input.getCmdOption("-col");
                    int columnIndex = 0;

                    try {
                        columnIndex = std::stoi(column);
                    }
                    catch (std::invalid_argument& e) {
                        // if no conversion could be performed
                    }
                    catch (std::out_of_range& e) {

                    }

                    //Add the statistic to the joblist.
                    if (columnIndex > 0 && columnIndex < columnCount)
                    {
                        if (statistic == "max")
                        {
                            jobList.push_back(new Max(columnIndex));
                        }
                        else if (statistic == "min")
                        {
                            jobList.push_back(new Min(columnIndex));
                        }
                        else if (statistic == "avg")
                        {
                            jobList.push_back(new Average(columnIndex));
                        }
                        else if (statistic == "med")
                        {
                            jobList.push_back(new Median(columnIndex));
                        }
                        else
                        {
                            //Default to all statistic if one was not specified.
                            jobList.push_back(new Max(columnIndex));
                            jobList.push_back(new Min(columnIndex));
                            jobList.push_back(new Average(columnIndex));
                            jobList.push_back(new Median(columnIndex));
                        }
                    }
                    else
                    {
                        std::cout << "Specified column is out of bounds of the data" << std::endl;
                    }

                }
                else
                {
                    std::cout << "Column number must be specified. Use -col <column>   EX: -col 1" << std::endl;
                }
            }

            //Do not read the file if there are no jobs to process.
            if (!jobList.empty())
            {
                //Read the file and perform all of the jobs in one pass.
                FileUtility::readAndRunJobs(inputFile, jobList);
            }

        }
        else
        {
            // File must be specified.
            std::cout << "File must be specified. Use -f <filename>" << std::endl;
            return 1;
        }

    }
    else
    {
        //-----------------------------Not using a single pass command----------------------------
        //-------------------These functions require the datasets to be in memory-----------------

        // Handle the inner join flag
        if (input.cmdOptionExists("-ij")) //Syntax : -ij file1.csv,file2.csv -on fieldname
        {
            if (input.cmdOptionExists("-on"))
            {
                std::string & joinField = input.getCmdOption("-on");
                std::vector<std::string> fileNames = FileUtility::split(input.getCmdOption("-ij"), ',');

                if (fileNames.size() >= 2) {
                    //Load the datasets into memory from files.
                    Dataset set1 = FileUtility::loadDataset(std::ifstream(fileNames[0]));

                    if (fileNames[0] == fileNames[1]) {
                        //Join on same file....
                        DatasetUtility::InnerJoinAndPrint(set1, set1, joinField);
                    }
                    else {
                        Dataset set2 = FileUtility::loadDataset(std::ifstream(fileNames[1]));
                        DatasetUtility::InnerJoinAndPrint(set1, set2, joinField);
                    }
                }
                else { std::cout << "Two files must be specified. Use -ij file1,file2"; }
            }
            else { std::cout << "Use the -on flag to specify which column to join on."; }
        }
        else if (input.cmdOptionExists("-oj")) //Syntax : -oj file1.csv,file2.csv -on fieldname
        {
            if (input.cmdOptionExists("-on"))
            {
                std::string & joinField = input.getCmdOption("-on");
                std::vector<std::string> fileNames = FileUtility::split(input.getCmdOption("-oj"), ',');

                if (fileNames.size() >= 2) {
                    //Load the datasets into memory from files.
                    Dataset set1 = FileUtility::loadDataset(std::ifstream(fileNames[0]));

                    if (fileNames[0] == fileNames[1]) {
                        //Join on same file....
                        DatasetUtility::OuterJoinAndPrint(set1, set1, joinField);
                    }
                    else {
                        Dataset set2 = FileUtility::loadDataset(std::ifstream(fileNames[1]));
                        DatasetUtility::OuterJoinAndPrint(set1, set2, joinField);
                    }
                }
                else { std::cout << "Two files must be specified. Use -ij file1,file2"; }
            }
            else { std::cout << "Use the -on flag to specify which column to join on."; }
        }
        else if (input.cmdOptionExists("-help")) {
            std::cout << "HyperCSV V1.0" << std::endl << std::endl;
            std::cout << "[Single File Commands]" << std::endl;
            std::cout << "-f is used to specify a filename. (Required for all single file commands)" << std::endl;
            std::cout << "\t Usage: -f <filename>" << std::endl;
            std::cout << "-s is used to gather statistics on a column." << std::endl;
            std::cout << "\t Usage: -s <stat> -col <columnIndex>" << std::endl;
            std::cout << "-e is used to perform a elementwise mathematic expression on columns" << std::endl;
            std::cout << "\t Usage: -e <expression>\t\tEX:  -e 1+5   OR   -e 1+6/2" << std::endl;
            std::cout << "-select is used to output select columns" << std::endl;
            std::cout << "\t Usage: -select <columnIdx,columnIdx,...>\tEX:  -select 1,2" << std::endl;
            std::cout << "-info is used to output information about a file." << std::endl;
            std::cout << "\t Usage: -info" << std::endl << std::endl;
            std::cout << "[Two File Commands]" << std::endl;
            std::cout << "-ij will perform an inner join on two datasets." << std::endl;
            std::cout << "\t Usage: -ij <file1,file2> -on <columnName>" << std::endl;
            std::cout << "-oj will perform an outer join on two datasets." << std::endl;
            std::cout << "\t Usage: -oj <file1,file2> -on <columnName>" << std::endl << std::endl;
            std::cout << "Example:  HyperCSV -f testfile.csv -s avg -col 1" << std::endl;
            std::cout << "Example:  HyperCSV -f testfile.csv -e 1+3/2 > output.txt" << std::endl;
            std::cout << "Example:  HyperCSV -ij file1.csv,file2.csv -on column1" << std::endl;
        }
        else {
            std::cout << "This program requires arguments. Get help with -help" << std::endl;
        }


    }//--- End of -f flag not found.


    return 0;
}

