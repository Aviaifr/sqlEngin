#ifndef _CONDITION_VALIDATOR_H_
#define _CONDITION_VALIDATOR_H_

#include <string>
#include "Scheme.h"
#include "Validator.h"

using namespace std;
class ConditionValidator : public Validator {
    string error;
    Scheme* scheme;

public:
    bool
    validate(string value) override;
    ConditionValidator(Scheme* s);

private:
    bool isSimpleCondition(string value, size_t startIndex);
    bool isComplexCondition(string value, string logicOp);
    bool isCondition(string value);
    bool isBracketsCondition(string value);
};

#endif