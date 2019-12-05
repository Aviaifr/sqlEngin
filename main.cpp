#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "QueryValidator.h"
#include "Scheme.h"

using namespace std;

int printMenu() {
    string op;
    cout << "Please select from the following options:" << endl;
    cout << "1 => Enter filename for file containig query per line (# will ignore line)" << endl;
    cout << "2 => Write your query" << endl;
    cout << "3 => Exit" << endl;
    getline(cin, op);
    return stoi(op);
}

void validateQuery(string queryString) {
    Scheme s("scheme.txt");
    QueryValidator v(&s);
    if (queryString.at(0) != '#') {
        cout << "validating query: " << queryString << endl;
        if (!v.validate(queryString)) {
            cout << "Query Validation: Error - " << v.getError() << endl
                 << endl;
        } else {
            cout << "Query Validation: OK" << endl
                 << endl;
        }
    }
}

void validateQueryFromFile(string fileName) {
    ifstream file(fileName);
    string queryString;
    while (getline(file, queryString)) {
        validateQuery(queryString);
    }
}

int main(int argc, char* argv[]) {
    Scheme s("scheme.txt");
    string queryString;
    int selection;
    do {
        selection = printMenu();
        string str;
        if (selection == 1) {
            cout << "Enter Filename" << endl
                 << ">";
            getline(cin, str);
            validateQueryFromFile(str);
        } else if (selection == 2) {
            cout << "Enter query" << endl
                 << ">";
            getline(cin, str);
            validateQuery(str);
        }
    } while (selection != 3);

    return 0;
}