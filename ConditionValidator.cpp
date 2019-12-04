#include "ConditionValidator.h"
#include "FieldValidator.h"
#include "IntValidator.h"
#include "OperatorValidator.h"
#include "StringLiteralValidator.h"

ConditionValidator::ConditionValidator(Scheme* s) {
    scheme = s;
}

bool ConditionValidator::isCondition(string value) {
    trim(value);
    bool res = isSimpleCondition(value, 0) ||
               isBracketsCondition(value) ||
               isComplexCondition(value, "AND") ||
               isComplexCondition(value, "OR");
    if (!res) {
        setError(value + " not a vaild condition");
    } else {
        setError("");
    }
    return res;
}

bool ConditionValidator::isComplexCondition(string value, string logicOp) {
    size_t logicOpLoc = 0, logicOpSize = logicOp.length(), startingIndex = 0;
    string upperCaseValue = stringToUpper(value);
    bool foundGoodCondition = false;
    while ((logicOpLoc = upperCaseValue.find(logicOp, startingIndex)) != string::npos && !foundGoodCondition) {
        startingIndex = logicOpLoc + 1;
        string left = value.substr(0, logicOpLoc);
        string right = value.substr(logicOpLoc + logicOpSize, value.length() - (logicOpLoc + logicOpSize));
        foundGoodCondition = isCondition(left) && isCondition(right);
    }

    return foundGoodCondition;
}

bool ConditionValidator::isSimpleCondition(string value, size_t startingIndex) {
    if (!startingIndex) {
        trim(value);
    }
    if (startingIndex == value.size()) {
        return false;
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
        FieldValidator fv(scheme);
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