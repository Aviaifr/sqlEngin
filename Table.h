#ifndef _TABLE_H_
#define _TABLE_H_

#include <string>
#include "Property.h"

using namespace std;

struct Table {
    string tName;
    size_t propertiesSize = 0;
    Property** properties;

public:
    Table(string tableString);
    Property* getProperty(string propName);
    ~Table();

private:
    void addProperty(string propString);
};

#endif