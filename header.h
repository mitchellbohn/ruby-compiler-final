#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

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
