#include<iomanip>
#include<stdlib.h>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "opcodes.h"
#include "Textcodes.h"
using namespace std;


  Textcodes::Textcodes(){
  length=0;
  }

 void Textcodes::newText(int locctr)
    {
        stringstream stemp;
        stemp<<setw(6)<<setfill('0')<<locctr;
        start = "T^" + stemp.str() + "^";
        length=0;
        currtext = "";
    }
 int  Textcodes::addText( vector<string> data)
    {
        Opcodes opcod;
        string opcode=opcod.getopcode(data[1]);
       if( opcode=="null" || (opcode== "4c" && data.size()<3 )  )
            return 0;
       currtext+="^";
       currtext+=opcode;
       if(data.size()<3 /* ||  symtab(data[2] == "null"  */ )
        currtext+="0000";
       else {
       // currtext+=symtab(data[2]);
       }
        length+=3;

    }
 string Textcodes::tostring()
  {
stringstream stemp;
        stemp<<setw(4)<<setfill('0')<<hex<<length;
        return start+  currtext;

 }
