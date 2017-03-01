#include "FileUtility.h"

/// @author Alexander Pinkerton

int FileUtility::columnCount(std::ifstream &filestream)
{
    //This will count the number of columns in a csv file.
    std::streampos oldPosition = filestream.tellg();
    filestream.clear();
    filestream.seekg(0, std::ios::beg);


    int lineCount = 0;
    std::string line;

    if (filestream.is_open()) {
        lineCount = FileUtility::getLineAndSplit(filestream, ',').size();
        //Resume the file stream where it was before.
        filestream.clear();
        filestream.seekg(oldPosition);
    } else {
        std::cout << "File could not be opened" << std::endl;
    }

    return lineCount;
}

int FileUtility::lineCount(std::ifstream &filestream)
{
    //This will simply count the lines when passed an already open filestream and then return the steam to where it was.
    std::streampos oldPosition = filestream.tellg();
    filestream.clear();
    filestream.seekg(0, std::ios::beg);


    int lineCount = 0;
    std::string line;

    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            ++lineCount;
        }
        //Resume the file stream where it was before.
        filestream.clear();
        filestream.seekg(oldPosition);
    } else {
        std::cout << "File was closed." << std::endl;
    }

    return lineCount;
}

std::vector<std::string> FileUtility::getFieldNames(std::ifstream &filestream)
{
    //This will return a vector containing field names.
    std::streampos oldPosition = filestream.tellg();
    filestream.clear();
    filestream.seekg(0, std::ios::beg);

    std::string line;

    std::vector<std::string> fieldnames;

    if (filestream.is_open()) {
        fieldnames = FileUtility::getLineAndSplit(filestream, ',');
        //Resume the file stream where it was before.
        filestream.clear();
        filestream.seekg(oldPosition);
    } else {
        std::cout << "File could not be opened" << std::endl;
    }

    return fieldnames;
}

std::unordered_map<int, Column> FileUtility::createColumns(std::ifstream &filestream, std::set<int> &&colNums)
{

    //Store the columns in a hashtable for speed and convenience.
    std::unordered_map<int, Column> columns;

    if (filestream.is_open()) {
        //Get the number of examples so we can allocate
        const int columnCount = lineCount(filestream);
        int lineNumber = 0;

        std::streampos oldPosition = filestream.tellg();
        filestream.clear();
        filestream.seekg(0, std::ios::beg);
        filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Skip field names.

        std::string currentLine;

        //Create map to hold our columns entries.

        for (int i : colNums) {
            columns[i] = Column();
        }


        //Parse every line of the csv file
        while (std::getline(filestream, currentLine)) {
            //For each line, extract the tokens for each column we want to create.
            std::vector<std::string> tokens = split(currentLine, ',');

            //Parse the tokens construct the columns in memory for later operations.
            for (unsigned int i = 0; i < tokens.size(); i++) {
                //If the column is in the set, save it.
                if (colNums.find(i) != colNums.end()) {
                    columns.at(i).addEntry(std::stof(tokens[i]));
                }
            }
            lineNumber++;
        }

        //Resume the file stream where it was before.
        filestream.clear();
        filestream.seekg(oldPosition);

    } else {
        std::cout << "File could not be opened." << std::endl;
    }

    return columns;
}

void FileUtility::printColumns(std::ifstream &filestream, std::set<int> &colNums)
{
    if (filestream.is_open()) {
        //Get the number of examples so we can allocate

        if (colNums.size() > 0) {

            const int columnCount = lineCount(filestream);
            int lineNumber = 0;


            std::streampos oldPosition = filestream.tellg();
            filestream.clear();
            filestream.seekg(0, std::ios::beg);

            //Print the field names
            std::string currentLine;
            std::getline(filestream, currentLine);
            std::vector<std::string> fields = FileUtility::split(currentLine, ',');
            for (unsigned int i = 0; i < fields.size(); i++) {
                //If the column is in the set, save it.
                if (colNums.find(i) != colNums.end()) {
                    std::cout << fields[i];
                    if (i < colNums.size()) {
                        std::cout << ",";
                    }
                }
            }
            std::cout << std::endl;


            //Parse every line of the csv file
            while (std::getline(filestream, currentLine)) {
                //For each line, extract the tokens for each column we want to create.
                std::vector<std::string> tokens = split(currentLine, ',');

                //Parse the tokens construct the columns in memory for later operations.
                for (unsigned int i = 0; i < tokens.size(); i++) {
                    //If the column is in the set, save it.
                    if (colNums.find(i) != colNums.end()) {
                        try {
                            std::cout << std::stof(tokens[i]);
                        }
                        catch (std::invalid_argument &e) {
                            // if no conversion could be performed
                        }
                        catch (std::out_of_range &e) {

                        }
                        catch (...) {

                        }

                        if (i < colNums.size()) {
                            std::cout << ",";
                        }
                    }
                }
                std::cout << std::endl;
                lineNumber++;
            }

            //Resume the file stream where it was before.
            filestream.clear();
            filestream.seekg(oldPosition);
        }


    } else {
        std::cout << "File could not be opened." << std::endl;
    }

}

Dataset FileUtility::loadDataset(std::ifstream &&filestream)
{
    //Store the columns in a hashtable for speed and convenience.
    std::unordered_map<int, Column> columns;
    std::vector<std::string> fieldNames;

    if (filestream.is_open()) {
        //Get the number of examples so we can allocate
        int colNums = FileUtility::columnCount(filestream);

        std::streampos oldPosition = filestream.tellg();
        filestream.clear();
        filestream.seekg(0, std::ios::beg);

        fieldNames = FileUtility::getLineAndSplit(filestream, ',');

        //Create the columns in the hashmap with the associated fieldname.
        for (int i = 0; i < colNums; i++) {
            columns[i] = Column(fieldNames[i]);
        }

        //Parse every line of the csv file and insert data into columns.
        std::string currentLine;
        while (std::getline(filestream, currentLine)) {
            //For each line, extract the tokens for each column we want to create.
            std::vector<std::string> tokens = split(currentLine, ',');

            //Parse the tokens construct the columns in memory for later operations.
            //TODO Handle types with generics or another solution.
            for (int i = 0; i < colNums; i++) {
                float entry = 0;
                try {
                    entry = std::stof(tokens[i]);
                }
                catch (std::invalid_argument &e) {
                    // if no conversion could be performed
                }
                catch (std::out_of_range &e) {

                }
                catch (...) {

                }

                columns[i].addEntry(entry);
            }

        }

        //Resume the file stream where it was before.
        filestream.clear();
        filestream.seekg(oldPosition);

    } else {
        std::cout << "File could not be opened." << std::endl;
    }

    Dataset result(columns);
    result.setFieldIndices(fieldNames);

    return result;
}

void FileUtility::readAndRunJobs(std::ifstream &filestream, std::list<SinglePassJob *> &jobList)
{
    if (filestream.is_open()) {

        filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Skip field names.

        std::string currentLine;

        //Read every line of the file.
        while (std::getline(filestream, currentLine)) {
            //Evaluate the entire expression on the columns row by row.
            std::vector<std::string> cells = split(currentLine, ',');

            //For each job in the list, send in the last col value or the row itself depending on jobtype.
            for (SinglePassJob *job : jobList) {
                if (job->columnNum != -1) {
                    //Job operates on single column
                    job->update(std::stof(cells[job->columnNum]));
                } else {
                    //Job operates on line...Need to refactor this.
                    job->update(cells);
                    std::cout << job->result << std::endl;
                }

            }
        }

    } else {
        std::cout << "File could not be opened." << std::endl;
    }

    //Output result for all single column jobs
    for (SinglePassJob *job : jobList) {
        if (job->columnNum != -1) {
            job->finish();
            std::cout << job->name << " " << job->result << std::endl;
        }
    }

    //Delete all of the jobs from the heap.
    for (SinglePassJob *job : jobList) {
        delete job;
        job = nullptr;
    }

}

std::vector<std::string> FileUtility::getLineAndSplit(std::ifstream &filestream, char &&delim)
{
    std::vector<std::string> result;
    std::string line;
    std::getline(filestream, line);
    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, delim)) {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty()) {
        // If there was a trailing comma then add an empty element.
        //result.push_back("");
    }

    return result;

}

template<typename T>
void FileUtility::split(const std::string &s, char delim, T result)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> FileUtility::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

