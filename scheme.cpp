#include "Scheme.h"
Scheme::Scheme(string fileName) {
    ifstream file(fileName);
    string tableString;
    sName = fileName.substr(0, fileName.find("."));
    while (getline(file, tableString)) {
        Table** newArray = new Table*[tableSize + 1];
        for (int index = 0; index < tableSize; index++) {
            newArray[index] = tables[index];
        }
        Table* newTable = new Table(tableString);
        newArray[tableSize] = newTable;
        delete[] tables;
        tables = newArray;
        tableSize++;
    }
}

Table* Scheme::getTable(string tableName) {
    for (int i = 0; i < tableSize; i++) {
        if (tableName.compare(tables[i]->tName) == 0) {
            return tables[i];
        }
    }
    return nullptr;
}