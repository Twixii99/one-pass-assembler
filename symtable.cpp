#include <unordered_map>
#include <iostream>

#include "symtable.h"

using namespace std;

Symtable* Symtable::unique = 0;
unordered_map<string, Sym*> symtable;

Symtable::Symtable() {}

Symtable* Symtable::getInstance() {
	if(Symtable::unique == 0) {
		Symtable::unique = new Symtable();
        Symtable::unique->insert("A", "0", true , 0, 0);
        Symtable::unique->insert("X", "1", true , 0, 0);
        Symtable::unique->insert("S", "4", true , 0, 0);
        Symtable::unique->insert("T", "5", true , 0, 0);
        Symtable::unique->insert("L", "2", true , 0, 0);
        Symtable::unique->insert("B", "3", true , 0, 0);
        Symtable::unique->insert("F", "6", true , 0, 0);
	}
	return Symtable::unique;
}

void Symtable::insert(string symbol, int loccnt, int flag) {
    Sym* got = getSymbol(symbol);
    if(got == nullptr) {
        Sym* sym = new Sym();
        sym->name = symbol;
        sym->address = "*";
        sym->operandsNeedThisLabel.push_back(make_pair(to_string(loccnt), flag));
        symtable[symbol] = sym;
    }
    else
        got->operandsNeedThisLabel.push_back(make_pair(to_string(loccnt), flag));
}

void Symtable::insert(std::string symbol, std::string address, bool abs, int block, int sec) {
	Sym* sym = getSymbol(symbol);
	if (sym == nullptr){
        sym = new Sym();
        symtable[symbol] = sym;
	}
    sym->name = symbol;
    sym->address = address;
    sym->absolute = abs;
    sym-> control_section = sec;
    sym -> program_block = block;
}

Sym* Symtable::getSymbol(string symbol) {
	std::unordered_map<string, Sym*>::const_iterator got = symtable.find(symbol);
    if(got == symtable.end())
    	return 0;
    return got->second;
}
