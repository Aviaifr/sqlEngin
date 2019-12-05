#ifndef _QUERY_VALIDATOR_H_
#define _QUERY_VALIDATOR_H_

#include <string>
#include "Scheme.h"
#include "Validator.h"

using namespace std;
class QueryValidator : public Validator {
    string error;
    Scheme* scheme;
    const string SELECT = "SELECT ";
    const string SELECT_DISTINCT = "SELECT DISTINCT ";
    const string FROM = " FROM ";
    const string WHERE = " WHERE ";

public:
    bool validate(string value) override;
    QueryValidator(Scheme* s);
};

#endif