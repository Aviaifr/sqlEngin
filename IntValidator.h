#ifndef _INT_VALIDATOR_H_
#define _INT_VALIDATOR_H_

#include <string>
#include "Validator.h"

using namespace std;
class IntValidator : public Validator {
	string error;
public:
	bool validate(string value) override;

private:
	bool isNumeric(string value);
	bool isDigit(char ch);
};



#endif