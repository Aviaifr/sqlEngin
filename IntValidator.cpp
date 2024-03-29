#include "IntValidator.h"

bool IntValidator::isDigit(char digit) {
    return digit <= '9' && digit >= '0';
}

bool IntValidator::isNumeric(string value) {
    if (value.length() == 0) {
        return true;
    }
    bool res = isDigit(value.at(0));
    if (!res) {
        setError(value + " is not a number");
    }

    return res && isNumeric(value.substr(1));
}
bool IntValidator::isSignedNumeric(string value){
	return (value.at(0) == '-' || value.at(0) == '+') && isNumeric(value.substr(1));
}

bool IntValidator::validate(string value) {
	trim(value);
	if (value.length() == 0) {
		return false;
	}
    return isNumeric(value) || isSignedNumeric(value);
}