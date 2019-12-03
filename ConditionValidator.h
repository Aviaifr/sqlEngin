#ifndef _CONDITION_VALIDATOR_H_
#define _CONDITION_VALIDATOR_H_

#include <string>
#include "Validator.h"

using namespace std;
class ConditionValidator : public Validator {
    string error;

public:
    bool validate(string value) override;

private:
    bool isSimpleCondition(string value);
};

#endif