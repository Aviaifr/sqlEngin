#include "ConditionValidator.h"
#include "FieldValidator.h"
#include "IntValidator.h"
#include "OperatorValidator.h"
#include "StringLiteralValidator.h"

bool ConditionValidator::isCondition(string value) {
    trim(value);
    bool res = isSimpleCondition(value, 0) || isBracketsCondition(value);
    if (!res) {
        setError(value + " not a vaild condition");
    } else {
        setError("");
    }
    return res;
}

bool ConditionValidator::isComplexCondition(string value) {
    size_t logicOpLoc;
    size_t logicOpSize = 0;
    if ((logicOpLoc = value.find("AND")) != string::npos) {
        logicOpSize = 3;
        //return isCondition() && isCondition()
    } else if ((logicOpLoc = value.find("AND")) != string::npos) {
        logicOpSize = 2;
    }
    if (logicOpSize) {
        //return isCondition() && isCondition();
    }
    return false;
}

bool ConditionValidator::isSimpleCondition(string value, size_t startingIndex) {
    if (!startingIndex) {
        trim(value);
    }
    if (value.at(startingIndex) == '"') {
        return isSimpleCondition(value, 1);
    }
    size_t closeQuatLoc, opLoc, opSize = 0;
    string right, left, op;
    if ((closeQuatLoc = value.find("\"", startingIndex)) == string::npos) {
        closeQuatLoc = startingIndex;
    }
    if ((opLoc = value.find("<", closeQuatLoc)) != string::npos) {
        opSize = 1;
        if (value[opLoc + 1] == '=' || value[opLoc + 1] == '>') {
            opSize = 2;
        }
    } else if ((opLoc = value.find(">", closeQuatLoc)) != string::npos) {
        opSize = 1;
        if (value[opLoc + 1] == '=') {
            opSize = 2;
        }
    } else if ((opLoc = value.find("=", closeQuatLoc)) != string::npos) {
        opSize = 1;
    }
    if (opSize) {
        right = value.substr(0, opLoc);
        op = value.substr(opLoc, opSize);
        left = value.substr(opLoc + opSize, value.length() - (opLoc + opSize));
        IntValidator iv;
        FieldValidator fv;
        StringLiteralValidator sv;
        OperatorValidator ov;
        bool aa = sv.validate(right);
        return (iv.validate(right) || fv.validate(right) || sv.validate(right)) && ov.validate(op) &&
               (iv.validate(left) || fv.validate(left) || sv.validate(left));
    }
    return false;
}

bool ConditionValidator::isBracketsCondition(string value) {
    if (value.at(0) == '(' && value.at(value.length() - 1) == ')') {
        return isCondition(value.substr(1, value.length() - 2));
    }
    return false;
}

bool ConditionValidator::validate(string value) {
    return isCondition(value);
}