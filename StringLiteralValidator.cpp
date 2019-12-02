#include "StringLiteralValidator.h"
bool StringLiteralValidator::isValidChar(char ch){
	return ch != '"';
}

bool StringLiteralValidator::isStringLiteral(string value){
	if (value.size() == 0){
		return true;
	}

	return isValidChar(value.at(0)) && isStringLiteral(value.substr(1));
}

bool StringLiteralValidator::validate(string value){
	bool res;
	if (value.at(0) != '"' || value.at(value.length() - 1) != '"'){
		setError("string literal not starting or not endint with \"");
		return false;
	}

	res = isStringLiteral(value.substr(1, value.length() - 2));
	if (!res){
		setError("unexpected \" in String literal " + value);
	}

	return res;
}