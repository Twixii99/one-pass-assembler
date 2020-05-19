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

    if (symb == nullptr || symb->address != "*" ||symb->operandsNeedThisLabel.size() == 0)
        return nullptr;

    return symb;
}
bool TextRecordFactory::addTextRecord(const vector<string>& statement, int locctr){

    int status = 0;
    Sym* symb = modifyPrevAddress(statement.at(0));
    if (symb != nullptr)
    {
        if (textRecord->tostring().size() > 0) {
            cout << textRecord->tostring() << '\n';
        }
        status = textRecord->addText(statement, symb);
        textRecord->newText(locctr);
    }
    else {
        // i dont know the limit :(
        if (textRecord->tostring().size() / 2 + numberOfBytes(statement) > 30){
            cout << textRecord->tostring() << '\n';
            textRecord->newText(locctr);
        }
        else if (textRecord->tostring().size() == 0)
            textRecord.newText(locctr);
        status = textRecord->addText(statement);
    }
    return status > 0;
}


int numberOfBytes(const vector<string>& statement)
{
    if (statement[1][0] == '+')
        return 4;
    else if (statement[1][statement[1].size()-1] == 'r' || statement[1][statement[1].size()-1] == 'R')
        return 2;
    return 3;
}


