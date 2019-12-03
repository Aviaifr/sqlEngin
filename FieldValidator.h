#ifndef _FIELD_VALIDATOR_H_
#define _FIELD_VALIDATOR_H_

#include <string>
#include "Validator.h"

using namespace std;
class FieldValidator : public Validator {
    string error;

public:
    bool validate(string value) override;

private:
    bool isField(string value);
};

#endif