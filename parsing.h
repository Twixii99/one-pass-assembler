#ifndef PARSING_H
#define PARSING_H
#include <vector>
#include <string>
#include "symtable.h"
#include "opcodes.h"

class parsing{

 void setnumofBytes();
 void setaddressmode();
 std::string label,code,operand;
 public:
   int numofBytes,modeaddress,locc;
   parsing(std::vector<std::string>);

};
#endif

