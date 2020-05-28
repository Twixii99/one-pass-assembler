#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

#include "TextRecordFactory.h"
#include "Textcodes.h"
#include "symtable.h"
using namespace std;

TextRecordFactory* TextRecordFactory::textRecFactory  = nullptr;

bool dataGenerationDirectives(string oper)
{
    if (oper == "BYTE" || oper == "WORD" || oper == "RESW" || oper == "RESB")
        return true;
    else
        return false;
}

TextRecordFactory::TextRecordFactory(){

    textRecord = new Textcodes();
}

TextRecordFactory* TextRecordFactory::getInstance()
{
    if (textRecFactory == nullptr)
        textRecFactory = new TextRecordFactory();

    return textRecFactory;
}
Sym* TextRecordFactory::modifyPrevAddress(string label) {

    if (label == "")
        return nullptr;
    Symtable* table = Symtable::getInstance();
    Sym* symb = table->getSymbol(label);

    if (symb == nullptr || symb->operandsNeedThisLabel.size() == 0)
        return nullptr;

    return symb;
}
void TextRecordFactory::addTextRecord(const vector<string>& statement, int locctr,long long flags,int numofbites ){

    int status = 0;
    Sym* symb = modifyPrevAddress(statement.at(0));
    if (dataGenerationDirectives(statement[1]))
    {
        textRecord->addText(statement, locctr);
    }
    else if (symb != nullptr)
    {
        if (textRecord->length > 0) {
            cout << textRecord->tostring() << '\n';
        }
       textRecord->addText(statement, symb);

        textRecord->newText(locctr);
    }
    else {
        // i dont know the limit :(
       if (textRecord->length  + numofbites >= 30){
            cout << textRecord->tostring() << '\n';
            textRecord->newText(locctr);
        }
       else  if(textRecord->length == 0)
        textRecord->newText(locctr);
      textRecord->addText(statement,flags,numofbites);
      //to see cuurtext
     cout<< textRecord->tostring()<<endl;
    }
}