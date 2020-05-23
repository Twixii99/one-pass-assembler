#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <string>


class parsing{

 void display(std::vector<std::string> &statement);
 void setnumofBytes( std::vector<std::string> &statement);
 void setaddressmode( std::vector<std::string> &statement);
 void checkParsing( std::vector<std::string> &statement);
 void parseDirective(std::vector<std::string> &statement);
 bool valid,pcrel ;
 public:
   int numofBytes,locc; long long modesaddress;
   parsing(std::vector<std::string> &statement);


};
#endif

