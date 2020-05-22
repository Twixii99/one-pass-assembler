#include <iostream>
#include <iomanip>
#include <list>
#include <unordered_map>
#include<bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>

#include "TextRecordFactory.h"
#include "symtable.h"
#include "Textcodes.h"
#include "opcodes.h"
#include "parsing.h"

//#include "Instruction_manip.h"

using namespace std;

bool caseInSensStringCompareCpp11(string str1, string str2);
void printErrorMessage();
bool isderctive(string s);
bool is_valid(vector<string> data);
bool label_validaty_checker(string str);
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
 Symtable* sys = Symtable::getInstance();
	sys->insert("COPY");
	Sym* syu = sys->getSymbol("COPY");
//	cout << syu-> name << "\t" << syu->address << endl;

  vector<string> tt;
  tt.push_back(""); tt.push_back("LDS");tt.push_back("ALPHA");
     parsing par(tt);
  TextRecordFactory* fac =TextRecordFactory::getInstance();
  fac->addTextRecord(tt,1000,par.modesaddress,par.numofBytes);
  tt.clear();
  tt.push_back(""); tt.push_back("LDA");tt.push_back("ALPHA");
   parsing par2(tt);
  fac->addTextRecord(tt,1003,par2.modesaddress,par2.numofBytes);


 /* fstream source_file {"source.txt", ios::in}; // object for the input file.
    // checking if the source file opened succesfully.
    if(!source_file) {
        cout << "failed to open the source code file";
        exit(EXIT_FAILURE);
    }
   string line;
   vector<string> data;
    while(getline(source_file, line)) {
        stringstream data_line(line);
        for(string s; data_line >> s; ){
        transform(s.begin(), s.end(), s.begin(), ::toupper );
            if(data.empty() && ( isderctive(s) || operations->getopcode(s)!= "null" ) )
               data.push_back("");
            data.push_back(s); }
           if(data.size()<3) data.push_back("");
           cout<<data[0]<<" " <<data[1]<<" "<<data[2]<<endl;
         parsing par(data);


           data.clear();
    }
   */
/*
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
   /* vector<string> data;
    while(getline(source_file, line)) {
        stringstream data_line(line);
        for(string s; data_line >> s; ){
            if(data.empty() || (isderctive(s) operations->getopcode(s)!= nullptr ) )
               data.push_back("");
            data.push_back(s); }
        if(data.size() > 3)
            if(data.at(3).at(0) != data.at(3).at(1))
                printErrorMessage();
        if(data.size()<3) data.push_back("");
        if(data.at(0).at(0) == '.') {
            data.clear();
            continue;
        }
        data.clear();
        ++lineNO;
    } */
  //  cout << operations << endl;
    Opcodes* ass = Opcodes::getInstance();
   // cout << ass << endl;
  //  cout << ass->getopcode("LDSs") << endl;
    return 0;
}

bool label_validaty_checker(string str) {
    return (isdigit(str.at(0)) ? false : true);
}

bool valid_line(vector<string> data){
  if( data[0] != "" && !label_validaty_checker(data[0])  )
     return false;
   if(isderctive(data[1])){
    if(data[0] == "" || data[2]=="")
        return false;
   }
     else{
   string opc =operations->getopcode(data[1]);
   if( opc =="null" ) return false;

   if ( (data[2]=="" && opc != "4c") || (data[2]!="" && !label_validaty_checker(data[2]) )  )
    return false;
     }

 return true;

}

bool isderctive(string s ){
  if(s == "WORD" ||s== "BYTE"|| s=="RESW"||s=="RESB"  )
    return true;
  return false;

}




void printErrorMessage() {
    cerr << "there may be an error in line " << ::lineNO << '.' << endl;
}
