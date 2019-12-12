#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

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
    return rubyLines;
}

vector<vector<string>> tokenizer(vector<string> rubyLines) {
	vector<vector<string>> tokenized;
	for(unsigned int i = 0; i<rubyLines.size(); i++) {
		stringstream ss(rubyLines[i]);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> tokens(begin, end);
		tokenized.push_back(tokens);
	}
	
	/*for (unsigned int i = 0; i < tokenized.size(); i++) {
		cout << "Row " << i << ": ";
		for (unsigned int j = 0; j < tokenized[i].size(); j++)
			cout << tokenized[i][j] << ' ';
		cout << endl;
	}*/
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
			} else if (tokens[i][j] == "gets()") {
				//callgets();
			} else if (tokens[i][j] == "def") {
				functions = def(tokens, i, functions);
				i = functions[0].end;
				j = tokens[i].size()-1;
			} else if (isFcn(tokens[i][j], functions)) {
				for (unsigned int k=0; k<functions.size(); k++) {
					if (tokens[i][j] == functions[k].name) {
						traverse(tokens, functions[k].start, functions[k].end);
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
