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
#include "symtable.h"
#include "parsing.h"
using namespace std;

 bool isderctiveee(string s ){
  if(s == "WORD" ||s== "BYTE"|| s=="RESW"||s=="RESB"  )
    return true;
  return false;

}
  parsing::parsing(vector<string> &statement){
      valid = true; pcrel=true;   numofBytes =0; modesaddress=0;
  if(Opcodes::getInstance()->getopcode(statement[1])== "null" && !isderctiveee(statement[1]) ){
   valid =false;
  }else {
     setnumofBytes(statement);
     if(numofBytes != 2 )
        setaddressmode(statement);
     checkParsing(statement);

  }
      cout<<valid<<" "<<numofBytes<< " "<< modesaddress<<" "<<endl;
  }

  void parsing::checkParsing( vector<string> &statement){

        if (numofBytes == 2)
        {
               string s1,s2; s1=statement[2][0]; s2=statement[2][2];
            if (statement[2].size() !=3 || statement[2][1] !=  ',' ||
                 Symtable::getInstance()->getSymbol(s1)== nullptr
                || Symtable::getInstance()->getSymbol(s2) == nullptr   ){
                valid = false;
            }
        }if((statement[2]=="" && Opcodes::getInstance()->getopcode(statement[1]) != "4c")) valid =false;
        if (statement[2].find(',') != std::string::npos && statement[2].find(",X") == std::string::npos)
            valid = false;

  }


   void  parsing::setnumofBytes( vector<string> &statement)
{
    if (statement[1][0] == '+')
       parsing::numofBytes = 4;
    else if (statement[1][statement[1].size()-1] == 'r' || statement[1][statement[1].size()-1] == 'R' || statement[1]=="RMO" )
        parsing::numofBytes=2;
        else
            parsing::numofBytes=3;

}

void parsing::setaddressmode( vector<string> &statement){
    if(numofBytes == 4)
        modesaddress +=1;

    if(statement[2][0] == '#'){
        if (statement[2].size() == 1)
            valid = false;

        modesaddress+=1<<4;
        if( statement[2].find(",X") !=  std::string::npos  ) {
            parsing::valid =false;
            return;
        }

    }
    else if(statement[2][0] == '@' ){
        if (statement[2].size() == 1)
            valid = false;
        modesaddress+=1<<5;
        if(statement[2].find(",X") !=  std::string::npos  ){
            parsing::valid =false;
            return;
        }
    }
    else{
        modesaddress+=1<<5;
        modesaddress+=1<<4;
         if(statement[2].find(",X") !=  std::string::npos  ){
            if (statement[2].size() > 2 || statement[2][statement[2].size() - 1] != 'X' || statement[2][statement[2].size() - 2] != ',')
                valid = false;
            modesaddress+=8;
         }
    }
    if (numofBytes == 3 && pcrel)
    {

         modesaddress+=1<<1;
    }


}
