#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "opcodes.h"

using namespace std;

unordered_map<string, string> optable;
fstream codes {"opcodes.txt", ios::in};

Opcodes* Opcodes::unique = 0;

Opcodes::Opcodes() {}

Opcodes* Opcodes::getInstance() {
	if(Opcodes::unique == 0) {
		Opcodes::unique = new Opcodes();
		unique->fill_optable();
	}

	return Opcodes::unique;
}

void Opcodes::fill_optable() {
    if(!codes) {
        cerr << "CAN\'T FOUND.";
  //      exit(EXIT_FAILURE);
    }

	string line;
	std::vector<string> vec;
	while(getline(codes, line)) {
	    stringstream ss(line);
	    string x, y;
	    getline(ss, x, ' ');
	    ss >> y;
	    ::optable[x] = y;
	}
}

string Opcodes::getopcode(string opcode) {
    std::unordered_map<string, string>::const_iterator got = optable.find(opcode);
    if(got == optable.end())
    	return "null";
    return got->second;
}

