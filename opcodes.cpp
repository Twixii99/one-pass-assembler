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

Opcodes::Opcodes() {
      this->fill_optable();
}

void Opcodes::fill_optable() {
      if(!codes) {
            cerr << "CAN\'T FOUND.";
            exit(EXIT_FAILURE);
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
      return optable.at(opcode);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}

