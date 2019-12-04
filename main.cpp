#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "FieldListValidator.h"
#include "Scheme.h"

using namespace std;

int main(int argc, char* argv[]) {
    Scheme s("scheme.txt");
    FieldListValidator v(&s);

    string a = "Name ,";
    // string error;
    // ConditionValidator v;
    if (!v.validate(a)) {
        cout << v.getError() << endl;
    } else {
        cout << "all good" << endl;
    }
    return 0;
}