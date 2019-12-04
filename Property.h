#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <string>

using namespace std;
struct Property {
    string pName;
    string pType;

public:
    Property(string propertyString) {
        size_t nekLoc = propertyString.find(":");
        pName = propertyString.substr(0, nekLoc);
        pType = propertyString.substr(nekLoc + 1, propertyString.size() - nekLoc - 1);
        trim(pName);
        trim(pType);
    }

private:
    void trim(string &strToTrim) {
        if (strToTrim.length() == 0) {
            return;
        }
        while (strToTrim.at(0) == ' ') {
            strToTrim = strToTrim.substr(1);
        }
        while (strToTrim.at(strToTrim.length() - 1) == ' ') {
            strToTrim = strToTrim.substr(0, strToTrim.length() - 1);
        }
    }
};

#endif