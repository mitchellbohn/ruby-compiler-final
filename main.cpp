#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

vector<string> scanner(string rubyFile);

vector<vector<string>> tokenizer(vector<string> rubyLines);

int main(int argc, char *argv[]) {
	//handling parameters and first possible errors
	if (argv[1] == nullptr)
		cout << "No parameters given, try again" << endl;
	else if (argv[2] != nullptr) //this check does not work
		cout << "Program executed with too many parameters!" << endl;
	else {
		//saves first parameter as file type, runs scanner, then tokenizer
		string parameter = argv[1];
		if (parameter == "-h")
			cout << "HELP: execute program with the name of the .rb file you wish to interpret to c++." << endl;
		else {
			vector<string> rubyLines = scanner(parameter);
			vector<vector<string>> tokenizedLines = tokenizer(rubyLines);
		}
	}
	return 0;
}

vector<string> scanner(string rubyFile) {
	//opens file to read lines
	ifstream infile;
	infile.open(rubyFile);
	if(!infile.is_open())
		cout << "error opening file \"" << rubyFile << "\", please check parameters..." << endl;
	else
		cout << "[1] File \"" << rubyFile << "\" is open..." << endl;
	
	//adds lines to Lines vector
	cout << "[2] Scanning..." << endl;
	int i = 0;
    vector<string> rubyLines;
    string currentLine;
    while(getline(infile, currentLine)) {
		rubyLines.push_back(currentLine);
        i++;
    }
    
    //closes file before exiting function, returning vector.
    infile.close();
    if(infile.is_open())
		cout << "Error closing file \"" << rubyFile << "\"..." << endl;
	else
		cout << "[3] File \"" << rubyFile << "\" closed..." << endl;
    return rubyLines;
}

vector<vector<string>> tokenizer(vector<string> rubyLines) {
	cout << "[4] Tokenizing lines..." << endl;
	vector<vector<string>> tokenized;
	for(unsigned int i = 0; i<rubyLines.size(); i++) {
		stringstream ss(rubyLines[i]);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> tokens(begin, end);
		//copy(tokens.begin(), tokens.end(), ostream_iterator<string>(cout, "\n"));
		tokenized.push_back(tokens);
	}
	cout << "Here is your 2D token Vector: " << endl;
	for (unsigned int i = 0; i < tokenized.size(); i++) {
		cout << "Row " << i << ": ";
		for (unsigned int j = 0; j < tokenized[i].size(); j++) {
			cout << tokenized[i][j] << ' ';
		}
		cout << endl;
	}
	return tokenized;
}
