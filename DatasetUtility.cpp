#include "DatasetUtility.h"

/// @author Alexander Pinkerton

DatasetUtility::DatasetUtility()
{
}

DatasetUtility::~DatasetUtility()
{
}

std::vector<std::string> DatasetUtility::GetJoinFields(Dataset &set1, Dataset &set2, std::string &joinField)
{
    //Create a set containing the output field names of the join.
    std::set<std::string> fields;

    for (auto i = set1.fieldIndices.begin();i != set1.fieldIndices.end(); i++) {
        fields.insert(i->first);
    }
    for (auto i = set2.fieldIndices.begin();i != set2.fieldIndices.end(); i++) {
        fields.insert(i->first);
    }

    return std::vector<std::string>(fields.begin(), fields.end());;
}

void DatasetUtility::PrintRow(std::vector<float> &row)
{
    for (std::vector<float>::iterator i = row.begin(); i < row.end(); i++) {
        std::cout << *i;
        if (i < row.end() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

void DatasetUtility::PrintRow(std::unordered_map<std::string, float> &row, std::vector<std::string> &fields)
{
    unsigned int i = 0;
    for (auto it = fields.begin(); it != fields.end(); it++) {
        i++;
        //If the row has a value for the column, print it, otherwise print null/0
        if (row.find(*it) != row.end()) {
            std::cout << row[*it];
        } else {
            std::cout << 0;
        }

        if (i < fields.size()) {
            std::cout << ",";
        }

    }
    std::cout << std::endl;
}

void DatasetUtility::PrintJoinFields(std::vector<std::string> &joinFields)
{
    //Output the field names of the join at the top.
    for (std::vector<std::string>::iterator it = joinFields.begin(); it < joinFields.end(); it++) {
        std::cout << *it;
        if (it < joinFields.end() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

/*------In order to increase speed. Inner Join is performed by hashing.-------*/
void DatasetUtility::InnerJoinAndPrint(Dataset &set1, Dataset &set2, std::string &joinField)
{
    //Create a pointer to the set with the least amount of rows.
    Dataset *smaller = set1.rowCount <= set2.rowCount ? &set1 : &set2;
    Dataset *larger = set1.rowCount > set2.rowCount ? &set1 : &set2;

    //Check if join field is in both datasets.
    if (set1.fieldIndices.find(joinField) != set1.fieldIndices.end() &&
        set2.fieldIndices.find(joinField) != set2.fieldIndices.end()) {
        //Hash the smaller table for memory overhead.
        std::unordered_map<float, std::vector<float>> smallerSet;

        //Hash every row of the smaller table by the join field.
        for (int i = 0; i < smaller->rowCount; i++) {
            std::vector<float> currentRow = smaller->getRow(i);
            float hash = currentRow[smaller->fieldIndices[joinField]];
            smallerSet[hash] = currentRow;
        }

        //Generate and output all of the fields from the Inner Join
        std::vector<std::string> outputFields = DatasetUtility::GetJoinFields(set1, set2, joinField);
        DatasetUtility::PrintJoinFields(outputFields);

        //Go through every row of larger set and check if there is a match on the joining column
        for (int i = 0; i < larger->rowCount; i++) {
            std::vector<float> currentRow = larger->getRow(i);
            float hash = currentRow[smaller->fieldIndices[joinField]];

            //Match was found
            if (smallerSet.find(hash) != smallerSet.end()) {
                //Construct output row from both rows.
                std::unordered_map<std::string, float> output;
                std::vector<float> row1 = currentRow;
                std::vector<float> row2 = smallerSet[hash];
                for (unsigned int i = 0; i < row1.size(); i++) {
                    output[larger->fieldNames[i]] = row1[i];
                }
                for (unsigned int i = 0; i < row2.size(); i++) {
                    output[smaller->fieldNames[i]] = row2[i];
                }

                DatasetUtility::PrintRow(output, outputFields);

            }
        }
    } else {
        std::cout << " Both sets do not have field: " << joinField << std::endl;
    }

}

/*------In order to increase speed. Outer Join is performed by hashing.-------*/
void DatasetUtility::OuterJoinAndPrint(Dataset &set1, Dataset &set2, std::string &joinField)
{
    //TODO: This currently is hashing both sets, it may be possible to reduce this overhead with indexing.
    //Create a pointer to the set with the least amount of rows.
    Dataset *smaller = set1.rowCount <= set2.rowCount ? &set1 : &set2;
    Dataset *larger = set1.rowCount > set2.rowCount ? &set1 : &set2;

    //Check if join field is in both datasets.
    if (set1.fieldIndices.find(joinField) != set1.fieldIndices.end() &&
        set2.fieldIndices.find(joinField) != set2.fieldIndices.end())
    {
        //Hash the smaller table for memory overhead.
        std::unordered_map<float, std::vector<float>> smallerSet;
        std::unordered_map<float, std::vector<float>> largerSet;

        //Hash every row of the smaller table by the join field.
        for (int i = 0; i < smaller->rowCount; i++) {
            std::vector<float> currentRow = smaller->getRow(i);
            float hash = currentRow[smaller->fieldIndices[joinField]];
            smallerSet[hash] = currentRow;
        }

        //Hash every row of the larger table by the join field.
        for (int i = 0; i < larger->rowCount; i++) {
            std::vector<float> currentRow = larger->getRow(i);
            float hash = currentRow[larger->fieldIndices[joinField]];
            largerSet[hash] = currentRow;
        }

        //Generate and output all of the fields from the Inner Join
        std::vector<std::string> outputFields = DatasetUtility::GetJoinFields(set1, set2, joinField);
        DatasetUtility::PrintJoinFields(outputFields);

        //Go through every row of larger set and check if there is a match on the joining column
        for (int i = 0; i < larger->rowCount; i++) {
            std::vector<float> currentRow = larger->getRow(i);
            float hash = currentRow[smaller->fieldIndices[joinField]];

            //Match was found
            if (smallerSet.find(hash) != smallerSet.end()) {
                //Construct output row from both rows.
                std::unordered_map<std::string, float> output;

                //Extract matching row from hash.
                std::vector<float> row2 = smallerSet[hash];

                //Add all the values from each row to the output.
                for (unsigned int i = 0; i < currentRow.size(); i++) {
                    output[larger->fieldNames[i]] = currentRow[i];
                }
                for (unsigned int i = 0; i < row2.size(); i++) {
                    output[smaller->fieldNames[i]] = row2[i];
                }
                DatasetUtility::PrintRow(output, outputFields);

            } else {
                //No match. Only print out the current row from traversal.
                std::unordered_map<std::string, float> output;
                for (unsigned int i = 0; i < currentRow.size(); i++) {
                    output[larger->fieldNames[i]] = currentRow[i];
                }
                DatasetUtility::PrintRow(output, outputFields);
            }
        }


        //Go through every row of smaller set and check if there is a match on the joining column
        for (int i = 0; i < smaller->rowCount; i++) {
            std::vector<float> currentRow = smaller->getRow(i);
            float hash = currentRow[larger->fieldIndices[joinField]];

            //Records that don't match
            if (largerSet.find(hash) == largerSet.end())
            {
                std::unordered_map<std::string, float> output;
                for (unsigned int i = 0; i < currentRow.size(); i++) {
                    output[smaller->fieldNames[i]] = currentRow[i];
                }
                DatasetUtility::PrintRow(output, outputFields);
            }

        }
    } else {
        //Bypass hashing and just do a super quick full outer.

        std::vector<std::string> outputFields = DatasetUtility::GetJoinFields(set1, set2, joinField);
        DatasetUtility::PrintJoinFields(outputFields);

        for (int i = 0; i < set1.rowCount; i++) {
            std::vector<float> currentRow = set1.getRow(i);
            std::unordered_map<std::string, float> output;
            for (unsigned int i = 0; i < currentRow.size(); i++) {
                output[set1.fieldNames[i]] = currentRow[i];
            }
            DatasetUtility::PrintRow(output, outputFields);
        }

        for (int i = 0; i < set2.rowCount; i++) {
            std::vector<float> currentRow = set2.getRow(i);
            std::unordered_map<std::string, float> output;
            for (unsigned int i = 0; i < currentRow.size(); i++) {
                output[set2.fieldNames[i]] = currentRow[i];
            }
            DatasetUtility::PrintRow(output, outputFields);
        }

    }

}


//-f testfilefloat.csv -ij set1.csv,set2.csv -on id
//-f testfilefloat.csv -ij a.csv,b.csv -on A