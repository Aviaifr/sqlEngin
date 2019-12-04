#include "FieldListValidator.h"
#include "FieldValidator.h"

FieldListValidator::FieldListValidator(Scheme* s) {
    scheme = s;
    fieldValidator = new FieldValidator(scheme);
}

bool FieldListValidator::isFieldList(string str) {
    trim(str);
    if (str.size() == 0) {
        return false;
    }
    size_t commaLoc;
    if ((commaLoc = str.find(",")) == string::npos) {
        return fieldValidator->validate(str);
    }
    return fieldValidator->validate(str.substr(0, commaLoc)) && isFieldList(str.substr(commaLoc + 1, str.size() - commaLoc));
}

bool FieldListValidator::validate(string value) {
    trim(value);
    bool res = isFieldList(value);
    if (!res) {
        setError("TODO UPDATE ERROR");
    }

    return res;
}