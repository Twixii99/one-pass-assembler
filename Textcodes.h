#ifndef TEXTCODES_H
#define TEXTCODES_H
#include <vector>
#include <string>
#include "symtable.h"

class Textcodes{
    std::string currtext,start;

 public:
    int length;
   Textcodes();
  void  newText(int locctr);
  void addText( std::vector<std::string> data);
  void addText(std::vector<std::string> data,Sym* label);
  std::string tostring();
};
#endif
