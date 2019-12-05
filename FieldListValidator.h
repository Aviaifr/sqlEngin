#ifndef _FIELD_LIST_VALIDATOR_H_
#define _FIELD_LIST_VALIDATOR_H_

#include <string>
#include "FieldValidator.h"
#include "Scheme.h"
#include "Validator.h"

using namespace std;

class FieldListValidator : public Validator {
    string error;
    Scheme* scheme;
    FieldValidator* fieldValidator;

public:
    bool
    validate(string value) override;
    FieldListValidator(Scheme* s);

private:
    bool isFieldList(string str);
    bool isField(string str);
};

#endif