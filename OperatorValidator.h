#ifndef _OPERATOR_VALIDATOR_H_
#define _OPERATOR_VALIDATOR_H_

#include <string>
#include "Validator.h"

using namespace std;
class OperatorValidator : public Validator {
    string error;

public:
    bool validate(string value) override;

private:
    bool isOperator(string value);
};

#endif