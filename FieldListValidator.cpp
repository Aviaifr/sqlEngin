#include "FieldListValidator.h"
#include "FieldValidator.h"

FieldListValidator::FieldListValidator(Scheme* s) {
    scheme = s;
    fieldValidator = new FieldValidator(scheme);
}

bool FieldListValidator::isField(string str) {
    bool isfieldExist = fieldValidator->validate(str);
    if (!isfieldExist) {
        setError(fieldValidator->getError());
    }
    return isfieldExist;
}

bool FieldListValidator::isFieldList(string str) {
    trim(str);
    size_t commaLoc;
    bool isfieldExist;
    string field;
    if ((commaLoc = str.find(",")) == string::npos) {
        return isField(str);
    } else {
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
        return isField(field) && isFieldList(fieldList);
    }
}

bool FieldListValidator::validate(string value) {
    trim(value);
    if (value.size() == 0) {
        setError("Column list is empty");
    }
    return isFieldList(value);
}