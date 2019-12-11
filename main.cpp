#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <regex>

using namespace std;

/* 0 string
 * 1 bool
 * 2 int
 */
class Value {
	public:
	string name;
	int valType;
	string value;
};

class Function {
	public:
	string name;
	int start;
	int end;
	
};

vector<string> scanner(string rubyFile);

vector<vector<string>> tokenizer(vector<string> rubyLines);

void traverse(vector<vector<string>> tokens, int start, int end);

int puts(vector<vector<string>> tokens, int row);

int def(vector<vector<string>> tokens, int row);

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
			vector<vector<string>> tokens = tokenizer(rubyLines);
			traverse(tokens, 0, tokens.size()-1);
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
		tokenized.push_back(tokens);
	}
	cout << "Here is your 2D token Vector: " << endl;
	for (unsigned int i = 0; i < tokenized.size(); i++) {
		cout << "Row " << i << ": ";
		for (unsigned int j = 0; j < tokenized[i].size(); j++)
			cout << tokenized[i][j] << ' ';
		cout << endl;
	}
	return tokenized;
}

void traverse(vector<vector<string>> tokens, int start, int end) {
	cout << "traversing..." << endl;
	vector<Value> values;
	string currentCase;
	for(int i = start; i < end; i++) {
		for (unsigned int j = 0; j < tokens[i].size(); j++) {
			if (j == 0 && tokens[i][j] == "puts") {
				i = puts(tokens, i);
				j = tokens[i].size()-1;
			} else if (tokens[i][j] == "def") {
				i = def(tokens, i);
			} else if (tokens[i][j] == "puts") {
			} else if (tokens[i][j] == "puts") {
			} else {
				if(tokens[i][j+1] == "=") {
					cout << "CAUGHT ELSE ROW: " << i << endl;
					//TODO: regex to determine val type.
					/*cout << "HERE!" << endl;
					Value *p = new Value;
					p->name = tokens[i][j];
					p->valType = 0;
					p->value = tokens[i][j+2];
					values.push_back(*p);
					cout << "NAME HERE: " << values[0].name << endl;*/
				}
			}
			
		}
	}
	return;
}

int puts(vector<vector<string>> tokens, int row) {
	unsigned int col = 1;
	bool done;
	
	if (tokens[row][col].front() == '\'') {
		if(tokens[row][col].back() == '\'') {
			cout << tokens[row][col].substr(1, tokens[row][col].size()-2) << endl;
			return row+1;
		} else {
			cout << tokens[row][col].substr(1) << ' ';
			col++;
			done = false;
			while(!done) {
				while (col < tokens[row].size()) {
					if (tokens[row][col].back() == '\'') {
						done = true;
						cout << tokens[row][col].substr(0, tokens[row][col].size()-1);
						col = tokens[row].size();
					} else {
						cout << tokens[row][col] << ' ';
						col++;
					}
				}
				col = 0;
				row++;
				cout << endl;
			}
		}
	} else if (tokens[row][col].front() == '\"') {
		if(tokens[row][col].back() == '\"') {
			cout << tokens[row][col].substr(1, tokens[row][col].size()-1) << endl;
			return row+1;
		} else {
			cout << tokens[row][col].substr(1) << ' ';
			col++;
			done = false;
			while(!done) {
				while (col < tokens[row].size()) {
					if (tokens[row][col].back() == '\"') {
						done = true;
						cout << tokens[row][col].substr(0, tokens[row][col].size()-1);
						col = tokens[row].size();
					} else {
						cout << tokens[row][col] << ' ';
						col++;
					}
				}
				col = 0;
				row++;
				cout << endl;
			}
		}
	} else {
		cout << "perhaps a variable, or lack of quotes? Moving on..." << endl;
		return row+1;
	}
	return row-1;
}

bool isVar(string name) {
	return true;
}

int def(vector<vector<string>> tokens, int row) {
	Function *p = new Function;
	p->name = tokens[row][1];
	while(tokens[row][0] != "end") {
		row++;
	}
	p->end = row;
	cout << "name: " << p->name << endl;
	return row;
}
