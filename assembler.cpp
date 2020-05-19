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
#include "symtable.h"

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

Opcodes* operations = Opcodes::getInstance();

/*int main()
{
    fstream source_file {"source.txt", ios::in}; // object for the input file.

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
  /*  vector<string> data;
    while(getline(source_file, line)) {
        stringstream data_line(line);

        for(string s; data_line >> s; )
            data.push_back(s);

        if(data.size() > 3)
            if(data.at(3).at(0) == data.at(3).at(1) == '\\')
                printErrorMessage();

        if(data.at(0).at(0) == '.') {
            data.clear();
            continue;
        }
        ++lineNO;
        cout << operations->getopcode("LDS") << endl;
    }
} */



// bool isdirective(string s){
//     if(s == "WORD" ||s== "BYTE"|| s=="RESW"||s=="RESB"  )
//         return true;
//     return false;
// }

// bool valid_line(vector<string> data){
//     if( data[0] != "" && !label_validaty_checker(data[0])  )
//         return false;
//     if(isdirective(data[1]))
//         if(data[0] == "" || data[2]=="")
//             return false;
//     else {
//         string opc =operations->getopcode(data[1]);
//         if( opc =="null" ) return false;
//         if ((data[2]=="" && opc != "4c") || (data[2]!="" && !label_validaty_checker(data[2])))
//             return false;
//     }
//     return true;
// }
