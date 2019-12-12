#pragma once

int puts(vector<vector<string>> tokens, int row, vector<Variable> variables) {
	unsigned int col = 1;
	bool done;
	bool dblQuotes = false;
	if (tokens[row][col] == "gets()") {
		cout << callgets() << endl;
		row++;
		return row;
	}else if (tokens[row][col].front() == '\"') {
		dblQuotes = true;
	}
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

string callgets() {
	string str;
	getline(cin, str);
	return str;
}

vector<Variable> setVariable(vector<string> line, vector<Variable> variables) {
	Variable *p = new Variable;
	p->name = line[0];
	p->varType = 0; //TODO: get varType
	bool dblQuote = false;
	if (line[2] == "gets()") {
		p->value = callgets();
		variables.push_back(*p);
		return variables;
	}else if (line[2].front() == '\"') {
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
	variables.push_back(*p);
	return variables;
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
