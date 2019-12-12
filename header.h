#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 0 string
 * 1 bool
 * 2 int
 */
class Variable {
	public:
	string name;
	int varType;
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

int puts(vector<vector<string>> tokens, int row, vector<Variable> variables);

string callgets();

vector<Function> def(vector<vector<string>> tokens, int row, vector<Function> functions);

vector<Variable> setVariable(vector<string> line, vector<Variable> variables);

bool isVar(string name, vector<Variable> variables);

bool isFcn(string name, vector<Function> functions);
