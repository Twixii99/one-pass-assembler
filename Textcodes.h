#ifndef TEXTCODES_H
#define TEXTCODES_H
#include <vector>
#include <string>
#include "symtable.h"

class Textcodes{
    std::string currtext,start;

 public:
     bool valid;
    int length;
    std::string objString;
   Textcodes();
  void newText(int locctr);
  void addText( std::vector<std::string> data,long long flags, int numofbites, int locctr);
  void addText(std::vector<std::string> data,Sym* label);
  void addText(std::vector<std::string> data, int locctr);
  void adjCurrText(int flag, std::string address, std::string locctr);
  std::string tostring();
};
#endif
