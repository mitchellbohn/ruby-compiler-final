#include <iostream>

#include "header.h"
#include "interpret.h"
#include "ruby.h"

using namespace std;

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
