#ifndef _SCHEME_H_
#define _SCHEME_H_

#include <fstream>
#include <iostream>
#include <string>
#include "Table.h"

using namespace std;
struct Scheme {
    string sName;
    size_t tableSize = 0;
    Table** tables;

public:
    Scheme(string filename);
    Table* getTable(string tableName);
};

#endif