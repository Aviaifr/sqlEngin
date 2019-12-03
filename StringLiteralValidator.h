#ifndef _STRING_LITERAL_VALIDATOR_H_
#define _STRING_LITETARL_VALIDATOR_H_

#include <string>
#include "Validator.h"

using namespace std;
class StringLiteralValidator : public Validator {
    string error;

public:
    bool validate(string value) override;

private:
    bool isStringLiteral(string value);
    bool isValidChar(char ch);
};

#endif