# HyperCSV

# Debian Installation
```sh
$ cd HyperCSV
$ cmake .
$ make
```

# Windows Installation
Launch "Developer Command Prompt for VS" and navigate to the HyperCSV directory
```sh
cl *.cpp *.hpp /Fe.\HyperCSV.exe
```

# Usage
| Argument | Description |
| ------ | ------ |
| -f filename | Specifies a file to perform operation on |
| -e expression | Performs an elementwise operation on columns |
| -s statistic -col columnIndex| Generates statistics for selected column [min, max, med, avg, all]|
| -select colIdx,colIdx | Outputs selected columns from file |
| -info columnIndex | Displays information regarding a table |
| -ij file1,file2 -on columnName | Performs a column-based Inner Join on two tables |
| -oj file1,file2 -on columnName | Performs a column-based Outer Join on two tables |
| -help | Lists all commands and some examples. |

# Examples
| Feature | Example |
| ------ | ------ |
| Print Columns | -f filename.csv -select 1,2,3 |
| Column Arithmetic | -f filename.csv -e 1+3/2 |
| Column Statistcs | -f filename.csv -s med -col 1|
| Dataset Info | -f filename.csv -info |
| Arithmetic and Stats Combo | -f filename.csv -e 1+2 -s med -col 1|
| Inner Join | -ij file1.csv,file2.csv -on field1 |
| Outer Join | -oj file1.csv,file2.csv -on field1 |


# Implementation Overview
In order to increase speed and robustness to extremely large files, HyperCSV has two main modes of operation, single-file mode and dual-file mode. Single file mode allows all operations to be performed in one pass through the data. In this mode, each line will be sequentially fed into every job allowing the processing of multiple jobs without multiple reads of the data. In order to implement this, I created an abstract base class which contains an update method and result value which all derived classes must contain. This allows a number of different job implementations which can all be easily dispatched by a job list. 

I have implemented elementwise column expressions which allow the user to input a standard infix expression which is translated to postfix notation before being parsed and calculated while reading the file. This system allows a much faster way of doing complex column operations. This system could be improved in the future by allowing variables and constants.

Certain operations, however, require that certain data is accessed multiple times. In these circumstances, I have decided to use a different mode of operation which will load an entire csv into memory. This mode of operation is used by the Inner and Outer join methods. In order to implement the inner and outer join methods, I used a hash join strategy to allow for much faster joins when compared to simple nested loop joins.

### Future Improvements
 - Handle all data types instead of simply converting everything to float
 - Allow Column and Row elementwise Arithmetic which can be expressed with vectorized notation.
 - Multithreaded joins
 - Allow commands to chain together without having to output to a file and reading it back in.
 - Column output filter instead of printing columns.
