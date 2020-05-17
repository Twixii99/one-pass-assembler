#include <iostream>
#include <iomanip>
#include <list>
#include <unordered_map>
#include<bits/stdc++.h> 
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

#include "opcodes.h"
//#include "Instruction_manip.h"

using namespace std;

bool caseInSensStringCompareCpp11(string str1, string str2);
void printErrorMessage();

const int DEFAULT_BLOCK = 0;
const int DEFAULT_CSEC = 0;

const string default_name = "DEFAULT"; // if the programmer didn't set a name for the program.

int lineNO = 0;
int current_line = 0;

int blocksNo = 1;
int current_block = 0;

int secionsNo = 1;
int current_CSEC = 0;

int loccnt = 0;

int base_register = 0;
bool base_used = false;

int pc_register = 0;
bool pc_used = false;

// how labels should be represented
struct label_data {
    string address;
    bool absolute;
    int control_section;
    int program_block;
    list<string> operands_need_this_label;

    label_data(string address, bool absolute) {
        this->address = address;
        this->absolute = absolute;
    }

    void setLabel(string label) {
        this->operands_need_this_label.push_back(label);
    }
};

unordered_map<string, label_data> labels;        // symbol table
Opcodes* operations = Opcodes::getInstance();

int main()
{
   /* fstream source_file {"source.txt", ios::in}; // object for the input file.

    // checking if the source file opened succesfully.
    if(!source_file) {
        cout << "failed to open the source code file";
        exit(EXIT_FAILURE);
    }

    // defining sting to take line by line from the source program.
    string line;
    /**
     * vector contains main data.
     * label = vector.at(0).
     * operator = vector.at(1).
     * operand = vector.at(2).
    */
   /* vector<string> data;
    while(getline(source_file, line)) {
        stringstream data_line(line);

        for(string s; data_line >> s; )
            data.push_back(s);

        if(data.size() > 3) 
            if(data.at(3).at(0) != data.at(3).at(1)) 
                printErrorMessage();
            
        if(data.at(0).at(0) == '.') {
            data.clear();
            continue;
        }
        ++lineNO;
    }*/
    cout << operations << endl;
    Opcodes* ass = Opcodes::getInstance();
    cout << ass << endl;
    cout << ass->getopcode("LDS") << endl;
    return 0;
}

bool label_validaty_checker(string str) {
    return (isdigit(str.at(0)) ? false : true);
}

bool caseInSensStringCompareCpp11(string str1, string str2)
{
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    return str1.compare(str2) == 0;
}

void printErrorMessage() {
    cerr << "there may be an error in line " << ::lineNO << '.' << endl;
}