#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "QueryValidator.h"
#include "Scheme.h"

using namespace std;

char printMenu() {
    string op;
    cout << "Please select from the following options:" << endl;
    cout << "1 => Enter filename for file containig query per line (# will ignore line)" << endl;
    cout << "2 => Write your query" << endl;
    cout << "q => Exit" << endl;
    getline(cin, op);
	if (op.size() == 0){
		op = 'a';
	}
    return op.at(0);
}

bool validateQuery(string queryString) {
    Scheme s("scheme.txt");
    QueryValidator v(&s);
    bool success;
    cout << "validating query: " << queryString << endl;
    success = v.validate(queryString);
    if (!success) {
        cout << "Query Validation: Error - " << v.getError() << endl
             << endl;
    } else {
        cout << "Query Validation: OK" << endl
             << endl;
    }
    return success;
}

void validateQueryFromFile(string fileName) {
    ifstream file(fileName);
    string queryString;
    size_t total = 0, countGood = 0;
    if (!file) {
        cout << "File not found" << endl;
        return;
    }
    cout << "----------Processing file " << fileName << " ----------" << endl
         << endl;
    while (getline(file, queryString)) {
        if (queryString.at(0) != '#') {
            total++;
            if (validateQuery(queryString)) {
                countGood++;
            }
        }
    }
    cout << "----------Processed " << total << " Queries, " << countGood << " Success, " << (total - countGood) << " Failed----------" << endl
         << endl;
}

int main(int argc, char* argv[]) {
    char selection;
    do {
        selection = printMenu();
        string str;
        if (selection == '1') {
            cout << "Enter Filename" << endl
                 << ">";
            getline(cin, str);
            validateQueryFromFile(str);
        } else if (selection == '2') {
            cout << "Enter query" << endl
                 << ">";
            getline(cin, str);
            validateQuery(str);
        }
    } while (selection != 'q');

    return 0;
}