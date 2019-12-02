#include "IntValidator.h"

bool IntValidator::isDigit(char digit){
	return digit < '9' && digit >'0';
}

bool IntValidator::isNumeric(string value){
	if (value.size() == 0){
		return true;
	}
	bool res = isDigit(value.at(0));
	if (!res){
		setError(value + " is not a number");
	}
	
	return res && isNumeric(value.substr(1));
}

bool IntValidator::validate(string value){
	return isNumeric(value);
}