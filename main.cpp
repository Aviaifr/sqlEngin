#include <algorithm>
#include <iostream>
#include <string>
#include "OperatorValidator.h"

using namespace std;

int main(int argc, char *argv[]) {
    string a = " avihai      is     awesome  a a  s   0";
    cout << "Started" << endl;
    string error;
    OperatorValidator v;
    if (!v.validate(a)) {
        cout << v.getError();
    } else {
        cout << "all good";
    }
    return 0;
}