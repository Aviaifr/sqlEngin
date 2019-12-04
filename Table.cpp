#include "Table.h"

Table::Table(string tableString) {
    size_t openBrackets = tableString.find("(");
    if ((openBrackets = openBrackets) != string::npos) {
        tName = tableString.substr(0, openBrackets);
        string propertiesStr = tableString.substr(openBrackets + 1, tableString.size() - openBrackets - 2);
        size_t startingIndex = 0, commaLoc;
        while ((commaLoc = propertiesStr.find(",", startingIndex)) != string::npos) {
            addProperty(propertiesStr.substr(startingIndex, commaLoc - startingIndex));
            startingIndex = commaLoc + 1;
        }
        addProperty(propertiesStr.substr(startingIndex, propertiesStr.size() - startingIndex));
    }
}

void Table::addProperty(string propString) {
    Property** newArray = new Property*[propertiesSize + 1];
    for (int index = 0; index < propertiesSize; index++) {
        newArray[index] = properties[index];
    }
    Property* newProp = new Property(propString);
    newArray[propertiesSize] = newProp;
    delete[] properties;
    properties = newArray;
    propertiesSize++;
}

Property* Table::getProperty(string propName) {
    for (int i = 0; i < propertiesSize; i++) {
        if (propName.compare(properties[i]->pName) == 0) {
            return properties[i];
        }
    }
    return nullptr;
}