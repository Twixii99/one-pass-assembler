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

    static TextRecordFactory* getInstance();
    bool addTextRecord(const std::vector<std::string> &statement, int locctr);
};



#endif // FACTORY
