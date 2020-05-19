#ifndef TEXTCODES_H
#define TEXTCODES_H
#include <vector>
#include <string>
#include "symtable.h"

class Textcodes{
    std::string currtext,start;
    int length;
 public:
   Textcodes();
  void  newText(int locctr);
  int addText( std::vector<std::string> data);
  int addText(std::vector<std::string> data,Sym* label);
  std::string tostring();
};
#endif
