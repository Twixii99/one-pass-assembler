#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <string>


class parsing {

 void setnumofBytes( std::vector<std::string> &statement);
 void setaddressmode( std::vector<std::string> &statement);
 void checkParsing( std::vector<std::string> &statement);
 void parseDirective(std::vector<std::string> &statement);
 int strToInt(char sign, std::string oper1, std::string oper2);
 void clear();
 bool valid,pcrel ;
 public:
   parsing();
   int parseExpression(std::string exp);
   int display(std::vector<std::string> &statement);
   int numofBytes,locc; long long modesaddress;
   bool isValid();
   bool isDirective(std::string);
};

#endif

