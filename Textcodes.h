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
  void addText( std::vector<std::string> data,long long flags, int numofbites);
  void addText(std::vector<std::string> data,Sym* label);
  void addText(std::vector<std::string> data, int locctr);
  std::string tostring();
};
#endif
