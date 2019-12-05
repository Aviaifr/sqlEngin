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
        if (tableSize) {
            delete[] tables;
        }
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

void Scheme::filterTables(string tablesToKeep) {
    size_t commaLoc, currentLoc = 0, tableCount = 0;
    Table** filteredArray;
    tablesToKeep = tablesToKeep + ",";
    while ((commaLoc = tablesToKeep.find(",", currentLoc)) != string::npos) {
        Table** newArray = new Table*[tableCount + 1];
        for (int index = 0; index < tableCount; index++) {
            newArray[index] = filteredArray[index];
        }
        string tableString = tablesToKeep.substr(0 + currentLoc, commaLoc - currentLoc);
        trim(tableString);
        Table* tablePtr = getTable(tableString);
        newArray[tableCount] = tablePtr;
        if (tableCount) {
            delete[] filteredArray;
        }
        filteredArray = newArray;
        tableCount++;
        currentLoc = commaLoc + 1;
    }
    delete[] tables;
    tables = filteredArray;
    tableSize = tableCount;
}

void Scheme::trim(string& strToTrim) {
    if (strToTrim.length() == 0) {
        return;
    }
    while (strToTrim.at(0) == ' ') {
        strToTrim = strToTrim.substr(1);
    }
    while (strToTrim.at(strToTrim.length() - 1) == ' ') {
        strToTrim = strToTrim.substr(0, strToTrim.length() - 1);
    }
}

Property* Scheme::getProperty(string propertyString) {
    size_t pointLoc;
    Table* tbl;
    if ((pointLoc = propertyString.find(".")) != string::npos) {
        string tblName = propertyString.substr(0, pointLoc);
        string propName = propertyString.substr(pointLoc + 1, propertyString.size() - pointLoc - 1);
        Table* tablePtr = getTable(tblName);
        if (!tablePtr) {
            return nullptr;
        }
        return tablePtr->getProperty(propName);
    } else {
        for (int i = 0; i < tableSize; i++) {
            Property* prop = tables[i]->getProperty(propertyString);
            if (prop) {
                return prop;
            }
        }
    }
    return nullptr;
}

Scheme::~Scheme() {
    for (int i = 0; i < tableSize; i++) {
        delete tables[i];
    }
    delete[] tables;
}