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

// bool caseInSensStringCompareCpp11(string str1, string str2);
// void printErrorMessage();
// bool isderctive(string s);
// bool is_valid(vector<string> data);
// bool label_validaty_checker(string str);
void increasingloccnt(vector<string> &statement);
bool dataGenerationDirective(string oper);
const int DEFAULT_BLOCK = 0;
const int DEFAULT_CSEC = 0;

const string default_name = "DEFAULT"; // if the programmer didn't set a name for the program.

int lineNO = 1;
int current_line = 1;

int blocksNo = 1;
int current_block = 0;

int secionsNo = 1;
int current_CSEC = 0;

int loccnt = 0;

bool codevalide=true;
bool pcUse;

int base_register = 0;
bool base_used = false;

int pc_register = 0;
bool pc_used = false;

TextRecordFactory* fac = nullptr;
Opcodes* operations = nullptr;
Symtable* sys = nullptr;
parsing par;
int main()
{
    operations = Opcodes::getInstance();
    sys = Symtable::getInstance();
    fac =TextRecordFactory::getInstance();

    fstream source_file {"source.txt", ios::in}; // object for the input file.
    // checking if the source file opened succesfully.
    if(!source_file) {
        exit(EXIT_FAILURE);
    }
    ofstream objcode,looping,opsymtab;
    objcode.open("output.txt");looping.open("looping.txt");opsymtab.open("opsymtab.txt");
    string line;
    vector<string> data;
    while(getline(source_file, line)) {
      stringstream data_line(line);
      for(string s; data_line >> s; ) {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        if(data.empty() && (par.isDirective(s) || operations->getopcode(s)!= "null" || s[0]=='+'))
          data.push_back("");
        data.push_back(s);
      }
      if(data.size() < 3) data.push_back("");
      int x = par.parseExpression(data[2]);                   ///////////////        3lem
      if(x != -1) data[2] = to_string(x);
      string data2,data1;
      data1 = data[1];
      if (data[1] !="" && data[1][0]=='+')
      {
        data1=data[1].substr(1);
      }
      if(data[0] != "") {
        if(sys->getSymbol(data[0]) == nullptr || sys->getSymbol(data[0])->address =="*" ){
          sys->insert(data[0],to_string(loccnt),true,0,0);
          opsymtab<<data[0]<<"    "<<loccnt<<endl;
        }else{
            codevalide=false;
        }
      }
      if(data[2]!= ""  ) {
         data2=data[2];
        if(data[2][0] == '@' || data[2][0]=='#')
           data2 = data[2].substr(1);
        if(isalpha(data2[0]) && sys->getSymbol(data2) == nullptr) {
            sys->insert(data2, loccnt);
            opsymtab<<data[2] <<"   "<<sys->getSymbol(data2)->operandsNeedThisLabel.size()<<endl;
        } else codevalide=false;
      }
      par.display(data);
      if(par.isValid() && (!par.directive || (par.directive &&  dataGenerationDirective(data1))))
        fac->addTextRecord(data,loccnt,par.modesaddress,par.numofBytes);

      looping <<lineNO<<"    "<<loccnt<<"      " << data[0]<<"   "<<data[1]<<"   "<<data[2]<<endl;
      increasingloccnt(data);
      data.clear();
  }
    return 0;
}

/*bool label_validaty_checker(string str) {
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


*/

void printErrorMessage() {
    cerr << "there may be an error in line " << ::lineNO << '.' << endl;
}

void increasingloccnt(vector<string> &statement) {
    if(par.isDirective(statement[1])) {
        if(par.isValid())
          if(statement[1] == "START") {
            loccnt = par.display(statement);
            if(loccnt == 0)
              pcUse = 1;
          }
          if(statement[1] == "RESW" || statement[1] == "WORD" || statement[1] == "RESB" || statement[1] == "BYTE")
            loccnt += par.display(statement);
          else if(statement[1] == "ORG") {
            if(statement[1][0] > 64 && statement[1][0] < 91) {
              if(sys->getSymbol(statement[2]) != nullptr)
                loccnt = stoi(sys->getSymbol(statement[2])->address);
              else {
                codevalide = false;
              }
            } else {
              loccnt = stoi(statement[2]);
            }
          } else if(statement[1] == "EQU") {
              if(sys->getSymbol(statement[2]) != nullptr)
                codevalide = false;
              else
                sys->insert(statement[0], statement[2], true, 0, 0);
          }
    } else {
      loccnt += par.display(statement);
    }
}

bool dataGenerationDirective(string oper)
{
    if (oper == "BYTE" || oper == "WORD" || oper == "RESW" || oper == "RESB")
        return true;
    else
        return false;
}
