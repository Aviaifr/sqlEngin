#include "Validator.h"
#include <algorithm>

void Validator::trim(string &strToTrim) {
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

void Validator::removeDoubleSpaces(string &strToClean) {
    if (strToClean.length() == 0) {
        return;
    }
    size_t doubleSpacePos = strToClean.find("  ");
    while (doubleSpacePos != string::npos) {
        strToClean = strToClean.substr(0, doubleSpacePos + 1) + strToClean.substr(doubleSpacePos + 2, strToClean.length() - doubleSpacePos);
        doubleSpacePos = strToClean.find("  ");
    }
}

void Validator::setError(string e) {
    error = e;
}

string Validator::getError() {
    return error;
}

string Validator::stringToUpper(string str) {
    string strCopy = str;
    for_each(strCopy.begin(), strCopy.end(), [](char &c) {
        c = toupper(c);
    });
    return strCopy;
}