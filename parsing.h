#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <string>


class parsing {

 void setnumofBytes( std::vector<std::string> &statement);
 void setaddressmode( std::vector<std::string> &statement);
 void checkParsing( std::vector<std::string> &statement);
 void parseDirective(std::vector<std::string> &statement);
 void clear();
 bool valid,pcrel ;
 public:
   parsing();
   int display(std::vector<std::string> &statement);
   int numofBytes,locc; long long modesaddress;
   bool isValid();
   bool isDirective(std::string);
};

#endif

