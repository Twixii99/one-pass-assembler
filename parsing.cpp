#include<iomanip>
#include<stdlib.h>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>
#include <regex>

#include "opcodes.h"
#include "Textcodes.h"
#include "symtable.h"
#include "parsing.h"

using namespace std;

regex r(R"(^^\s*[-+]?((\d+(\.\d+)?)|(\d+\.)|(\.\d+))(e[-+]?\d+)?\s*$)");

unordered_map<string, string> directives = {
  {"NOBASE", ""},         // done
  {"LITORG", ""},
  {"EXTREF", ""},
  {"EXTDEF", ""},
  {"START", ""},         // done
  {"RESW", ""},          // done
  {"RESB", ""},			 // done
  {"BYTE", ""},          // done
  {"WORD", ""},          // done
  {"BASE", ""},          // done
  {"END", ""},           // done
  {"USE", ""},
  {"EQU", ""},           // done
  {"ORG", ""},           // done
};

bool isDirective(string s){
  unordered_map<string, string>::const_iterator got = directives.find(s);
  if(got != directives.end())
    return true;
  return false;
}

parsing::parsing() {
  parsing::valid = true; 
  parsing::pcrel = true;  
  parsing::numofBytes = 0; 
  parsing::modesaddress = 0;
  parsing::locc = 0;
}

int parsing::display(vector<string> &statement) {
	string str = statement[1];
	if(::isDirective(str)) {
		parseDirective(statement);
		parsing::valid = false;
	}
	else {
		if(statement[1][0] != '+')
		  str = statement[1].substr(1);
		valid = Opcodes::getInstance()->getopcode(str) != "null" ? true : false;
	}
	if(parsing::valid) {
		setnumofBytes(statement);
		if(numofBytes != 2)
		  setaddressmode(statement);
		checkParsing(statement);
	}
	return locc;
}

void parsing::checkParsing(vector<string> &statement) {
 	if (numofBytes == 2) {
        string s1,s2; s1=statement[2][0]; s2=statement[2][2];
    	if (statement[2].size() !=3 || statement[2][1] !=  ',' ||
        	Symtable::getInstance()->getSymbol(s1)== nullptr
        	|| Symtable::getInstance()->getSymbol(s2) == nullptr) {
        	valid = false;
    	}
    } 
    if ((statement[2]=="" && Opcodes::getInstance()->getopcode(statement[1]) != "4c")) 
    	valid =false;
  	if (statement[2].find(',') != std::string::npos && statement[2].find(",X") == std::string::npos)
     	valid = false;
}

void  parsing::setnumofBytes(vector<string> &statement) {
  if (statement[1][0] == '+')
     parsing::numofBytes = 4;
  else if (statement[1][statement[1].size()-1] == 'r' || statement[1][statement[1].size()-1] == 'R' || statement[1] == "RMO")
    parsing::numofBytes = 2;
  else
    parsing::numofBytes = 3;
}

void parsing::setaddressmode(vector<string> &statement) {
    if (numofBytes == 4)
        modesaddress += 1;
	if (statement[2][0] == '#'){
        if (statement[2].size() == 1)
            valid = false;
        modesaddress += 1 << 4;
        if(statement[2].find(",X") != std::string::npos) {
            parsing::valid =false;
            return;
        }
    } else if(statement[2][0] == '@' ){
        if (statement[2].size() == 1)
            valid = false;
        modesaddress += 1 << 5;
        if(statement[2].find(",X") != std::string::npos){
            parsing::valid =false;
            return;
        }
    }
    else{
        modesaddress += 1 << 5;
        modesaddress += 1 << 4;
         if(statement[2].find(",X") !=  std::string::npos) {
            if (statement[2].size() > 2 || statement[2][statement[2].size() - 1] != 'X' || statement[2][statement[2].size() - 2] != ',')
                valid = false;
            modesaddress += 8;
         }
    }
    if (numofBytes == 3 && pcrel)
    {
         modesaddress += 1 << 1;
    }
}
 
void parsing::parseDirective(vector<string> &statement) {
	if(statement[1] == "START")
		parsing::locc = !(statement[2] == "") ? regex_match(statement[0], r) ? stoi(statement[1]) : 0 : 0;
	else if(statement[1] == "RESW" || statement[1] == "RESB" || statement[1] == "BYTE" || statement[1] == "WORD") {
		if(statement[2] == "" || statement[0] == "") {
			parsing::valid = 0;
			return;
		}
		switch (statement[1][3]) {
			case 'B' :
				if(regex_match(statement[2], r))
					parsing::locc += stoi(statement[2]); 
				break;
			case 'W' :
				if(regex_match(statement[2], r))
					parsing::locc += stoi(statement[2]) * 3;
				break;
			case 'D' :
				if(regex_match(statement[2], r))
					parsing::locc += 3;
				break;
			default :
				if((statement[2][0] == 'X' || statement[2][0] == 'C'))
					if(statement[2][1] == statement[2][statement[2].size()-1] == '\'')
						locc += statement[2].substr(2).size()-1;
		}
	}
	else if(statement[1] == "BASE" && statement[2] == "" || statement[1] == "NOBASE" && !(statement[2] == "")) {
		parsing::valid = 0;
		return;
	}
	else if(statement[1] == "END") {
		if(!(statement[2] == "") || !regex_match(statement[1], r)) {
			parsing::valid = 0;
			return;
		}
	}
	else if(statement[1] == "ORG")
		if(statement[2] == "" || !(statement[0] == "")) {
			parsing:valid = 0;
			return;
		}
	else if(statement[1] == "EQU")
		if(statement[0] == "" || statement[2] == "") {
			parsing::valid = 0;
			return;
		}
}