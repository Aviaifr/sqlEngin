#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_

#include <string>
using namespace std;
class Validator {
    string error = "";

public:
    virtual bool validate(string value) = 0;
    string getError();

protected:
    void trim(string &strToTrim);
    void removeDoubleSpaces(string &strToClean);
    void setError(string e);
    string stringToUpper(string str);
};

#endif