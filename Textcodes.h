#ifndef TEXTCODES_H
#define TEXTCODES_h
#include <vector>
#include <string>
class Textcodes{
    std::string currtext,start;
    int length;
 public:
   Textcodes();
  void  newText(int locctr);
  int addText( std::vector<std::string> data);
  std::string tostring();
};
#endif
