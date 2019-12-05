#include "FieldValidator.h"

bool FieldValidator::validate(string value) {
    bool found = isField(value);
    if (!found && getError().size() == 0) {
        setError("Column '" + value + "' not found in scheme");
    }
    return found;
}

bool FieldValidator::isField(string value) {
    size_t pointLoc;
    trim(value);
    bool foundProp = false;
    if ((pointLoc = value.find(".")) != string::npos) {
        string tblName = value.substr(0, pointLoc);
        string propName = value.substr(pointLoc + 1, value.size() - pointLoc - 1);
        foundProp = isPropertyExists(tblName, propName);
    } else {
        for (int i = 0; i < scheme->tableSize; i++) {
            bool existInCurrent = isPropertyExists(scheme->tables[i]->tName, value);
            if (existInCurrent) {
                if (foundProp) {
                    setError("Column '" + value + "'  is ambiguous");
                    return false;
                }
                foundProp = existInCurrent;
            }
        }
    }

    return foundProp;
}

FieldValidator::FieldValidator(Scheme* s) {
    scheme = s;
}

bool FieldValidator::isPropertyExists(string tableName, string PropName) {
    Table* t = scheme->getTable(tableName);
    if (!t) {
        setError("'" + tableName + "' not a table in scheme or not included in FROM clause");
        return false;
    }
    Property* p = t->getProperty(PropName);
    return !!p;
}