#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "header.h"

using namespace std;

vector<string> scanner(string rubyFile);

vector<vector<string>> tokenizer(vector<string> rubyLines);

void traverse(vector<vector<string>> tokens, int start, int end);

int puts(vector<vector<string>> tokens, int row, vector<Variable> variables);

vector<Function> def(vector<vector<string>> tokens, int row, vector<Function> functions);

vector<Variable> setVariable(vector<string> line, vector<Variable> variables);

bool isVar(string name, vector<Variable> variables);

bool isFcn(string name, vector<Function> functions);

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
			traverse(tokens, 0, tokens.size());
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
		
	//adds lines to Lines vector
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
	vector<Variable> variables;
	vector<Function> functions;
	for(int i = start; i < end; i++) {
		for (unsigned int j = 0; j < tokens[i].size(); j++) {
			if (j == 0 && tokens[i][j] == "puts") {
				i = puts(tokens, i, variables);
				j = tokens[i].size()-1;
			} else if (tokens[i][j] == "def") {
				functions = def(tokens, i, functions);
				i = functions[0].end;
				j = tokens[i].size()-1;
			} else if (isFcn(tokens[i][j], functions)) {
				for (unsigned int k=0; k<functions.size(); k++) {
					if (tokens[i][j] == functions[k].name) {
						traverse(tokens, functions[k].start, functions[k].end-1);
						k = functions.size();
					}
				}
			}else if(!isVar(tokens[i][j], variables) && tokens[i][1] == "=") {
					variables = setVariable(tokens[i], variables);
				j = tokens[i].size()-1;
			}else{
				cout << "else" << endl;
			}
		}
	}
}

int puts(vector<vector<string>> tokens, int row, vector<Variable> variables) {
	unsigned int col = 1;
	bool done;
	bool dblQuotes = false;
	if (tokens[row][col].front() == '\"')
		dblQuotes = true;
	if (tokens[row][col].front() == '\'' || tokens[row][col].front() == '\"') {
		if((tokens[row][col].back() == '\'' && !dblQuotes) || (tokens[row][col].back() == '\"' && dblQuotes)) {
			cout << tokens[row][col].substr(1, tokens[row][col].size()-2) << endl;
			return row;
		} else {
			cout << tokens[row][col].substr(1) << ' ';
			col++;
			done = false;
			while(!done) {
				while (col < tokens[row].size()) {
					if ((tokens[row][col].back() == '\'' && !dblQuotes) || (tokens[row][col].back() == '\"' && dblQuotes)) {
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
		unsigned int i = 0;
		while (i < variables.size()) {
			if(variables[i].name == tokens[row][1]) {
				cout << variables[i].value << endl;
				i = variables.size();
			} else {
				i++;
			}
		}
		return row;
	}
	return row-1;
}

vector<Variable> setVariable(vector<string> line, vector<Variable> variables) {
	//try adding gets()!
	Variable *p = new Variable;
	p->name = line[0];
	bool dblQuote = false;
	if (line[2].front() == '\"') {
		dblQuote = true;
	}
	for(unsigned int i=2; i<line.size(); i++) {
		if ((line[i].front() == '\'' && !dblQuote) || (line[i].front() == '\"' && dblQuote)) {
			if ((line[i].back() == '\'' && !dblQuote) || (line[i].back() == '\"' && dblQuote)) {
				p->value.append(line[i].substr(1, line[i].size()-2));
			} else {
				p->value.append(line[i].substr(1));
				p->value.append(" ");
			}
		} else if ((line[i].back() == '\'' && !dblQuote) || (line[i].back() == '\"' && dblQuote)) {
			p->value.append(line[i].substr(0, line[i].size()-1));
		} else {
			p->value.append(line[i]);
			p->value.append(" ");
		}
		
	}
	p->varType = 0; //TODO: get varType
	variables.push_back(*p);
	return variables;
}

bool isVar(string name, vector<Variable> variables) {
	for (unsigned int i=0; i<variables.size(); i++) {
		if (name == variables[i].name) {
			return true;
		}
	}
	return false;
}

bool isFcn(string name, vector<Function> functions) {
	for (unsigned int i=0; i<functions.size(); i++) {
		if (name == functions[i].name) {
			return true;
		}
	}
	return false;
}

vector<Function> def(vector<vector<string>> tokens, int row, vector<Function> functions) {
	Function *p = new Function;
	p->name = tokens[row][1];
	p->start = row+1;
	while(tokens[row][0] != "end") {
		row++;
	}
	p->end = row;
	functions.push_back(*p);
	return functions;
}
