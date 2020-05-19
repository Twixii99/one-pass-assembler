#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <list>
#include <string>

struct Sym {
   std::string name;
   std::string address;
   bool absolute;
   int program_block;
   int control_section;
   std::list<std::string> operandsNeedThisLabel;
};

class Symtable {
   private:
      static Symtable* unique;
      Symtable();
   public:
      static Symtable* getInstance();
      void insert(std::string);
      void insert(std::string, std::string, bool, int, int);
      Sym* getSymbol(std::string);
};

#endif