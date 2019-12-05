#include "QueryValidator.h"
#include "ConditionValidator.h"
#include "FieldListValidator.h"
#include "TableListValidator.h"

QueryValidator::QueryValidator(Scheme* s) {
    scheme = s;
}

bool QueryValidator::validate(string value) {
    removeDoubleSpaces(value);
    trim(value);
    string allUpper = stringToUpper(value);
    string attributeList, tableList, condition;
    size_t currentLoc, skip = SELECT.size();

    if ((currentLoc = allUpper.find(SELECT_DISTINCT)) != string::npos) {
        skip = SELECT_DISTINCT.size();
    } else if ((currentLoc = allUpper.find(SELECT)) == string::npos) {
        setError("Parsing failed: No SELECT found");
        return false;
    }
    if ((currentLoc = allUpper.find(FROM, skip)) != string::npos) {  //FOUND FROM
        attributeList = value.substr(skip, currentLoc - skip);
        skip = currentLoc + FROM.size();  //skip = first location after from
    } else {
        setError("Parsing failed: No FROM found");
        return false;
    }
    size_t smiColLoc = value.find(";");
    if (smiColLoc == string::npos) {
        setError("Parsing failed: Are you missing a ';'?");
        return false;
    } else if (smiColLoc != value.size() - 1) {
        setError("Parsing failed: Unexpected ';' at " + smiColLoc);
        return false;
    }
    if ((currentLoc = allUpper.find(WHERE, skip)) != string::npos) {
        tableList = value.substr(skip, currentLoc - skip);
        skip = currentLoc + WHERE.size();
        condition = value.substr(skip, smiColLoc - skip);
    } else {
        tableList = value.substr(skip, smiColLoc - skip);
    }
    Validator* v = new TableListValidator(scheme);
    if (!v->validate(tableList)) {
        setError("Parsing <table_list> failed: " + v->getError());
        delete v;
        return false;
    }
    delete v;
    scheme->filterTables(tableList);
    v = new FieldListValidator(scheme);
    if (!v->validate(attributeList)) {
        setError("Parsing <attribute_list> failed: " + v->getError());
        delete v;
        return false;
    }
    delete v;
    if (condition.size() > 0) {
        v = new ConditionValidator(scheme);
        if (!v->validate(condition)) {
            setError("Parsing <condition> failed: " + v->getError());
            delete v;
            return false;
        }
        delete v;
    }
    return true;
}