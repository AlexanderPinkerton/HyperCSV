#ifndef HYPERCSV_ARGUMENTPARSER_H
#define HYPERCSV_ARGUMENTPARSER_H

#include <algorithm>
#include <vector>

// I decided to grab this easy argument parser so I could focus on the meat of the tool.
// A more robust Argument Parser will be needed to combine jobs in better ways.

class ArgumentParser {
public:
	ArgumentParser(int &argc, char **argv) {
		for (int i = 1; i < argc; ++i)
			this->tokens.push_back(std::string(argv[i]));
	}
	/// @author iain
	 std::string& getCmdOption(std::string && option) {
		std::vector<std::string>::iterator itr;
		itr = std::find(this->tokens.begin(), this->tokens.end(), option);
		if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
			return *itr;
		}
		return empty_string;
	}
	/// @author iain
	bool cmdOptionExists(std::string && option) {
		return std::find(this->tokens.begin(), this->tokens.end(), option)
			!= this->tokens.end();
	}
private:
	std::vector <std::string> tokens;
	std::string empty_string;
};





#endif //HYPERCSV_ARGUMENTPARSER_H
