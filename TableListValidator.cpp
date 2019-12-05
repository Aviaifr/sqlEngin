#include "TableListValidator.h"

bool TableListValidator::validate(string value) {
    trim(value);
    if (!value.size()) {
        setError("Table list is empty");
        return false;
    }
    return isTableList(value);
}

bool TableListValidator::isTableList(string value) {
    size_t commaLoc;
    if ((commaLoc = value.find(",")) == string::npos) {
        return isTable(value);
    }
    if (commaLoc == 0) {
        setError("Table list is empty");
        return false;
    }
    string tableStr = value.substr(0, commaLoc);
    string tableListStr = value.substr(commaLoc + 1, value.length() - commaLoc - 1);
    trim(tableListStr);
    if (tableListStr.size() == 0) {
        setError("Unexpected ',' in table list");
        return false;
    }
    return isTable(tableStr) && isTableList(tableListStr);
}

bool TableListValidator::isTable(string value) {
    Table* t = scheme->getTable(value);
    if (!scheme->getTable(value)) {
        setError("Table '" + value + "' does not exist");
        return false;
    }
    return true;
}

TableListValidator::TableListValidator(Scheme* s) {
    scheme = s;
}