#include "OperatorValidator.h"

bool OperatorValidator::isOperator(string value) {
    if (value.length() == 1) {
        return value.compare("=") == 0 || value.compare("<") == 0 || value.compare(">") == 0;
    } else if (value.length() == 2) {
        return value.compare("<>") == 0 || value.compare("<=") == 0 || value.compare(">=") == 0;
    }
    return false;
}

bool OperatorValidator::validate(string value) {
    bool res;
    trim(value);
    res = isOperator(value);
    if (!res) {
        setError(value + " is not a valid operator");
    }

    return res;
}