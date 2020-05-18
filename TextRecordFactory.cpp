#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

#include "TextRecordFactory.h"
#include "Textcodes.h"
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

bool TextRecordFactory::isitNewPanel(string word) {

    transform(word.begin(), word.end(), word.begin(), ::tolower);

    if (word == "byte" || word == "word" || word == "resw" || word == "resb")
        return true;
    return false;


}
bool TextRecordFactory::addTextRecord(const vector<string>& statement, int locctr){

    int status = 0;
    if (isitNewPanel(statement.at(1)))
    {
        if (textRecord->tostring().size() > 0) {
            cout << textRecord->tostring() << '\n';
        }
        textRecord->newText(locctr);
        status = textRecord->addText(statement);
        cout << textRecord->tostring() << '\n';
        textRecord->newText(locctr);
    }
    else {
        // i dont know the limit :(
        if (textRecord->tostring().size() > 30){
            cout << textRecord->tostring() << '\n';
             textRecord->newText(locctr);
        }
        status = textRecord->addText(statement);
    }
    return status > 0;
}





