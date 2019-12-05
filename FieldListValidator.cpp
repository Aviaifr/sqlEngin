#include "FieldListValidator.h"
#include "FieldValidator.h"

FieldListValidator::FieldListValidator(Scheme* s) {
    scheme = s;
    fieldValidator = new FieldValidator(scheme);
}

bool FieldListValidator::isFieldList(string str) {
    trim(str);
    size_t commaLoc;
    if ((commaLoc = str.find(",")) == string::npos) {
        return fieldValidator->validate(str);
    }
    if (commaLoc == 0) {
        setError("Column list is empty");
        return false;
    }
    string field = str.substr(0, commaLoc);
    string fieldList = str.substr(commaLoc + 1, str.size() - commaLoc);
    trim(fieldList);
    if (fieldList.size() == 0) {
        setError("Unexpected ',' in column list");
        return false;
    }
    bool isfieldExist = fieldValidator->validate(field);
    if (!isfieldExist) {
        setError("Column '" + field + "' does not exist");
        return false;
    }
    return isfieldExist && isFieldList(fieldList);
}

bool FieldListValidator::validate(string value) {
    trim(value);
    if (value.size() == 0) {
        setError("Column list is empty");
    }
    return isFieldList(value);
}