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
  {"NOBASE", ""},        // done
  {"LITORG", ""},
  {"EXTREF", ""},
  {"EXTDEF", ""},
  {"START", ""},         // done
  {"RESW", ""},          // done
  {"RESB", ""},			     // done
  {"BYTE", ""},          // done
  {"WORD", ""},          // done
  {"BASE", ""},          // done
  {"END", ""},           // done
  {"USE", ""},
  {"EQU", ""},           // done
  {"ORG", ""},           // done
};

bool parsing::isDirective(string s){
  unordered_map<string, string>::const_iterator got = directives.find(s);
  if(got != directives.end())
    return true;
  return false;
}

void parsing::clear() {
  parsing::valid = true;
  parsing::pcrel = true;
  parsing::numofBytes = 0;
  parsing::modesaddress = 0;
  parsing::locc = 0;
  parsing::directive = 0;
}

parsing::parsing() {}

int parsing::display(vector<string> &statement) {
    parsing::clear();
	string str = statement[1];
	if(parsing::isDirective(str)) {
		parseDirective(statement);
        parsing::directive = true;
        return parsing::locc;
	}
	else {
		if(statement[1][0] == '+')
		  str = statement[1].substr(1);
		valid = Opcodes::getInstance()->getopcode(str) == "null" ? false : true;
	}
	if(parsing::valid && !directive) {
		setnumofBytes(statement);
		if(numofBytes != 2)
            setaddressmode(statement);
		checkParsing(statement);
	}
  return parsing::numofBytes;
}

void parsing::checkParsing(vector<string> &statement) {
 	if (numofBytes == 2) {
        string s1,s2; s1=statement[2][0]; s2=statement[2][2];
    	if (statement[2].size() !=3 || statement[2][1] !=  ',' ||
        	Symtable::getInstance()->getSymbol(s1)== nullptr
        	|| Symtable::getInstance()->getSymbol(s2) == nullptr) {
        	valid = false;
    	}
    	return;
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
		parsing::locc = !(statement[2] == "") ? regex_match(statement[0], r) ? std::stoul(statement[2], nullptr, 16) : 0 : 0;
	else if(statement[1] == "RESW" || statement[1] == "RESB" || statement[1] == "BYTE" || statement[1] == "WORD") {
		if(statement[2] == "" || statement[0] == "") {
			parsing::valid = 0;
			return;
		}
		switch (statement[1][3]) {
			case 'B' :
				if(regex_match(statement[2], r))
					parsing::locc += stoi(statement[2]);
        else
          parsing::valid = 0;
				break;
			case 'W' :
				if(regex_match(statement[2], r)) {
					parsing::locc += stoi(statement[2]) * 3;
				}
        else
          parsing::valid = 0;
				break;
			case 'D' :
				if(regex_match(statement[2], r))
					parsing::locc += 3;
        else
          parsing::valid = 0;
				break;
			default :
				if((statement[2][0] == 'X' || statement[2][0] == 'C')) {
					if(statement[2][1] == '\'' && statement[2][statement[2].size()-1] == '\'')
						locc += statement[2].substr(2).size()-1;
          else
            parsing::valid = 0;
        } else
          parsing::valid = 0;
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
	else if(statement[1] == "ORG") {
		if(statement[2] == "") {
			parsing:valid = 0;
			return;
		}
  }
	else if(statement[1] == "EQU") {
		if(statement[0] == "" || statement[2] == "") {
			parsing::valid = 0;
			return;
		}
  }
}

int parsing::parseExpression(string exp) {

    if (exp.size() > 2 && exp[exp.size() - 1] == 'X' && exp[exp.size() - 2] == ',')
      exp = exp.substr(0, exp.size() - 2);

    if (exp[0] == '#' || exp[0] == '@')
      exp = exp.substr(1, exp.size() - 1);

    int signInd = 0;
    int cnt = 0;
    for (int i = 0; i < exp.size(); i++){
        if (!isdigit(exp[i])) {
            signInd = i;
            cnt++;
        }
    }
    if (cnt == 0)
      return stoi(exp);

    if (cnt != 1 || signInd == 0 || signInd == exp.size() - 1)
        return -1;
    return strToInt(exp[signInd],exp.substr(0, signInd), exp.substr(signInd + 1, exp.size() - 1 - signInd));
}

int parsing::strToInt(char sign, string oper1, string oper2) {
    switch (sign) {
        case '+' : return stoi(oper1) + stoi(oper2);
        case '-' : return stoi(oper1) - stoi(oper2);
        case '*' : return stoi(oper1) * stoi(oper2);
        case '/' : return stoi(oper1) / stoi(oper2);
        default  : return -1;
    }
}

bool parsing::isValid() {
  return valid;
}
