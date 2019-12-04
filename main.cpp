#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "ConditionValidator.h"
#include "Scheme.h"

using namespace std;

int main(int argc, char* argv[]) {
    Scheme s("scheme.txt");
    string a = "\"andy\" = 2323 or 1231>123";
    // string error;
    // ConditionValidator v;
    // if (!v.validate(a)) {
    //     cout << v.getError() << endl;
    // } else {
    //     cout << "all good" << endl;
    // }
    return 0;
}