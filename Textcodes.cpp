#include<iomanip>
#include<stdlib.h>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <cstdio>

#include "opcodes.h"
#include "Textcodes.h"
#include "symtable.h"
using namespace std;


  Textcodes::Textcodes(){
    valid = true;
    length=0;
  }

  bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
 void Textcodes::newText(int locctr)
{
       if(length >0){

        stringstream lengthStream;
        lengthStream << setw(2) << setfill('0') << hex << length;
        string lenStr;
        lengthStream >> lenStr;

        objString+="\n"+ start + lenStr +currtext;
       }
        stringstream stemp;
        stemp<<setw(6)<<setfill('0')<< hex <<locctr;
        start = "T^" + stemp.str() + "^";
        length=0;
        currtext = "";
}

void  Textcodes::addText(vector<string> data,long long flags,int numofbites, int locctr)
{

       Opcodes* opcod = Opcodes::getInstance();
        string data1 = data[1];
       if(numofbites == 4)
            data1 = data1.substr(1, data1.size() - 1);
       string opcode = opcod->getopcode(data1);

       currtext+="^";

       Symtable* sys = Symtable::getInstance();
       string data2=data[2];
       if (data2[0] == '#' || data2[0] == '@')
        data2 = data2.substr(1, data2.size() - 1);
       if (data2.size() > 2 && data2[data2.size() - 1] == 'X' && data2[data2.size() - 2] == ',' && numofbites != 2) {
           data2 = data2.substr(0, data2.size() - 2);
       }
       //cout << data1 << ' ' << data2 << '\n';
       long long curraddress = 0;
       stringstream strs;
       strs.str("");
     if(is_number(data2)){
       flags &= 61;
       curraddress = stoi(data2);
       //cout << curraddress << "Makram" <<'\n';

     }else{

        Sym* syu = sys->getSymbol(data2);
        if( syu == nullptr || syu->address == "*"){
        curraddress = 0;
        flags &= 61;
       // cout<<"symm"<<endl;
       }
       else {
        strs << (syu->address);
        strs >> curraddress;
        strs.str("");
       }

    }
    long long objectCode=0;
    long long lopcode,lcurr;
    //std::string s = "0xfffefffe";
    lopcode = std::stoul(opcode, nullptr, 16);
    if (numofbites == 2)
    {
        cout << data[2] << opcode <<  endl;
        currtext += opcode + (sys->getSymbol(data[2].substr(0, 1))->address + sys->getSymbol(data[2].substr(2, 1))->address);
        length += 2;
        return;
    }
   /* strs.str("");
    strs << hex <<opcode;
    strs >> lopcode;*/
   // cout<<lopcode<<" opp1"<<endl;

    if ((flags & (1 << 4)) != 0 && numofbites != 2)
        lopcode++;
    if ((flags & (1 << 5)) != 0 && numofbites != 2)
        lopcode+=2;
    //cout<<lopcode<<" opp2"<<endl;
   // cout << currtext << endl;
        strs.clear();

    strs.str("");
    strs<<setw(2)<<setfill('0')<<hex<<lopcode;
    string sol;
    strs >> sol;

    currtext+=sol;
    //cout << currtext << "here 1" << endl;
   // cout<<"sda"<<lopcode<<endl;
   objectCode = curraddress;
    if (numofbites == 3){
        if ((flags & (1 << 1)) != 0)
        {
            objectCode -= (locctr + 3);
            if (objectCode  > 2047 || objectCode < -2048) {
                valid = false;
            }
            objectCode &= 8191;
        }
        for (int i = 0; i <= 3; i++){
            if ((flags & (1 << i)) != 0)
                objectCode |= (1 << (i + 12));
         }
    }
    else if (numofbites == 4){
        for (int i = 0; i <= 3; i++){
            if ((flags & (1 << i)) != 0)
                objectCode |= (1 << (i + 20));
         }
    }

      //cout << objectCode << "here 2" << endl;
      stringstream str2;
      //sol = "";
      if (numofbites == 3)
        str2<<setw(4)<<setfill('0')<<hex<<objectCode;
      else
        str2<<setw(6)<<setfill('0')<<hex<<objectCode;

      str2 >> sol;
      //sprintf(sol, "%X", objectCode);
      currtext+=sol;
      length+=numofbites;
    }
void Textcodes::addText(std::vector<std::string> data, Sym* label) {

    //cout << label->operandsNeedThisLabel.size() << "%%%%%%%%%%%%%%%%%%%\n";
    for (int i = 0; i < label->operandsNeedThisLabel.size(); i++)
    {
        stringstream stream;
        std::list<pair<std::string, int> >::iterator it = label->operandsNeedThisLabel.begin();
        std::advance(it, i);
        stream << setw(6) << setfill('0') << hex << std::to_string(stoi((*it).first) + 1);
        start = "T^" + stream.str() + "^";
        adjCurrText((*it).second,label->address, (*it).first);


        stringstream lengthStream;
        lengthStream << setw(2) << setfill('0') << hex << length;
        string lenStr;
        lengthStream >> lenStr;


        objString += "\n" + start + lenStr + "^" + currtext;
        start = currtext = "";
        length = 0;
    }
}

void Textcodes::adjCurrText(int flag, string address, string locctr)
{
    stringstream str;
    long long addInt = stoi(address);
    if (flag % 2  == 0){
        if ((flag & (1 << 1)) != 0)
        {
            addInt -= (stoi(locctr) + 3);
            if (addInt  > 2047 || addInt < -2048) {
                valid = false;
            }
            addInt &= 8191;
        }
        for (int i = 0; i <= 3; i++){
            if ((flag & (1 << i)) != 0)
                addInt |= (1 << (i + 12));
        }
        str << setw(4) << setfill('0') << hex << (addInt);
    }
    else if (flag % 2  == 1){
        for (int i = 0; i <= 3; i++){
            if ((flag & (1 << i)) != 0)
                addInt |= (1 << (i + 20));
         }
         str << setw(6) << setfill('0') << hex << (addInt);
    }
    str >> currtext;
    length = currtext.size() / 2;
    //cout << addInt << ' ' << length << '\n';
}

string ToHex(const string& s, bool upper_case /* = true */)
{
    ostringstream ret;
   // cout << s << "***************************" << endl;
    for (string::size_type i = 0; i < s.length(); ++i)
        ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];

    return ret.str();
}

void Textcodes::addText(std::vector<std::string> data, int locctr)
{

    if (data[1] == "RESW" || data[1] == "RESB")
    {
        if (length != 0) {
            cout << tostring() << '\n';
        }
        if (data[1] == "RESW")
            newText(locctr + 3 * stoi(data[2]));
        else
            newText(locctr +  stoi(data[2]));
    }
    else {
        if (data[1] == "WORD")
        {
            if (length + 3 > 30)
            {
                cout << tostring() << '\n';
                newText(locctr);
            }
            stringstream streamo;
            streamo << setw(6) << setfill('0') << hex << data[2];
         //   cout << data[2] << ' ' << stream.str() << "******&&&&&&&&&&&&&&&&&&&&&" << endl;
            string ans;
            streamo >> ans;
            streamo.str("");
            currtext += "^" + ans;
            length += 3;
        }
        else {
            string hexa;
            cout << "HELP" << endl;
            if (data[2][0] == 'C' || data[2][0] == 'c')
            {
                hexa = ToHex(data[2].substr(2, data[2].size() - 3), true);
            }
            else {
                hexa = data[2].substr(2, data[2].size() - 3);
            }
            if (length + (hexa.size() / 2) > 30)
            {
                cout << tostring() << '\n';
                newText(locctr);
            }
            currtext += "^" + hexa;
            length += (hexa.size() / 2);
        }
    }
}

 string Textcodes::tostring()
  {
        stringstream lengthStream;
        lengthStream << setw(2) << setfill('0') << hex << length;
        string lenStr;
        lengthStream >> lenStr;
        if(length > 0 )
            return  objString+ "\n" +start + lenStr + currtext;
        else
            return objString;
  }

