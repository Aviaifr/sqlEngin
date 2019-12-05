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
    return isSimpleCondition(value, 0) ||
           isBracketsCondition(value) ||
           isComplexCondition(value, "AND") ||
           isComplexCondition(value, "OR");
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
    if ((closeQuatLoc = value.find("\"", startingIndex)) == string::npos && startingIndex) {
        closeQuatLoc = startingIndex;
    } else {
        closeQuatLoc = 0;
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
        left = value.substr(0, opLoc);
        op = value.substr(opLoc, opSize);
        right = value.substr(opLoc + opSize, value.length() - (opLoc + opSize));
        return validateSimpleCondition(right, left, op);
    }
    return false;
}

bool ConditionValidator::validateSimpleCondition(string right, string left, string op) {
    IntValidator iv;
    FieldValidator fv(scheme);
    StringLiteralValidator sv;
    OperatorValidator ov;
    bool rightString = sv.validate(right);
    bool rightInt = iv.validate(right);
    bool rightField = fv.validate(right);
    bool leftString = sv.validate(left);
    bool leftInt = iv.validate(left);
    bool leftField = fv.validate(left);
    bool isOp = ov.validate(op);
    Property* rightProp = scheme->getProperty(right);
    Property* leftProp = scheme->getProperty(left);
    if (rightProp) {
        if (leftInt && rightProp->pType.compare("INTEGER") != 0) {
            setError("Cannot compare " + rightProp->pType + " To INTEGER at " + left + op + right);
            return false;
        }
        if (leftString && rightProp->pType.compare("STRING") != 0) {
            setError("Cannot compare " + rightProp->pType + " To STRING at " + left + op + right);
            return false;
        }
        if (leftProp) {
            if (rightProp->pType.compare(leftProp->pType) != 0) {
                setError("Cannot compare " + rightProp->pType + " To " + leftProp->pType + " at " + left + op + right);
                return false;
            }
        }
    } else if (leftProp) {
        if (rightInt && leftProp->pType.compare("INTEGER") != 0) {
            setError("Cannot compare " + leftProp->pType + " To INTEGER at " + left + op + right);
            return false;
        }
        if (rightString && leftProp->pType.compare("STRING") != 0) {
            setError("Cannot compare " + leftProp->pType + " To STRING at " + left + op + right);
            return false;
        }
    } else if (leftInt && !rightInt) {
        setError("Cannot compare INTEGER to STRING at " + left + op + right);
        return false;
    }

    return (rightString || rightInt || rightField) &&
           isOp &&
           (leftString || leftInt || leftField);
}

bool ConditionValidator::isBracketsCondition(string value) {
    if (value.size() > 0 && value.at(0) == '(' && value.at(value.length() - 1) == ')') {
        return isCondition(value.substr(1, value.length() - 2));
    }
    return false;
}

bool ConditionValidator::validate(string value) {
    bool res = isCondition(value);
    if (!res && getError().size() == 0) {
        setError(value + " not a vaild condition");
    }
    return res;
}