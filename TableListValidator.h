#ifndef _TABLE_LIST_VALIDATOR_H_
#define _TABLE_LIST_VALIDATOR_H_

#include <string>
#include "Scheme.h"
#include "Validator.h"

using namespace std;
class TableListValidator : public Validator {
    string error;
    Scheme* scheme;

public:
    bool validate(string value) override;
    TableListValidator(Scheme* s);

private:
    bool isTable(string value);
    bool isTableList(string value);
};

#endif