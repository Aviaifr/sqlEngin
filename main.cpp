#include <iostream>
#include "IntValidator.h"
#include "StringLiteralValidator.h"
#include "OperatorValidator.h"
#include <string>
#include <algorithm>

using namespace std;

int main(){
	string a = " avihai      is     awesome  a a  s   0";
	string error;
	OperatorValidator v;
	if (!v.validate(a)){
		cout << v.getError();
	}
	else
		cout << "all good";
	return 0;
}