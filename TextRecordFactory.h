#ifndef FACTORY
#define FACTORY
#include "Textcodes.h"
#include "symtable.h"
#include <vector>
#include <string>
using namespace std;
class TextRecordFactory {

private:
    Textcodes* textRecord;
    static TextRecordFactory* textRecFactory;
    TextRecordFactory();
    Sym* modifyPrevAddress(string label);
public:
    bool valid;
    static TextRecordFactory* getInstance();
    void breakText(int locctr);
    void addTextRecord(const std::vector<std::string> &statement, int locctr,long long flags, int numofbites);
     std::string gettextrecord();
};



#endif // FACTORY
