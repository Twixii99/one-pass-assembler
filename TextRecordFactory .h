#ifndef FACTORY
#define FACTORY
#include "Textcodes.h"
#include <vector>
#include <string>
using namespace std;
class TextRecordFactory {

private:
    Textcodes* textRecord;
    static TextRecordFactory* textRecFactory;
    TextRecordFactory();
    bool isitNewPanel(string word);
public:

    static TextRecordFactory* getInstance();
    bool addTextRecord(const std::vector<std::string> &statement, int locctr);
};



#endif // FACTORY
