#include <algorithm>
#include <iostream>
#include <string>
#include "ConditionValidator.h"

using namespace std;

int main(int argc, char *argv[]) {
    string a = "     (\"<\">=12) ";
    string error;
    ConditionValidator v;
    if (!v.validate(a)) {
        cout << v.getError() << endl;
    } else {
        cout << "all good" << endl;
    }
    return 0;
}