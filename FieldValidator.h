#ifndef _FIELD_VALIDATOR_H_
#define _FIELD_VALIDATOR_H_

#include <string>
#include "Scheme.h"
#include "Validator.h"

using namespace std;
class FieldValidator : public Validator {
    string error;
    Scheme* scheme;

public:
    bool validate(string value) override;
    FieldValidator(Scheme* s);

private:
    bool isField(string value);
    bool isPropertyExists(string tableName, string PropName);
};

#endif