#pragma once

#include <unordered_map>

#include "cSymbol.h"

using std::string;

class cSymbolTable
{
public:
    void InsertSymbol(cSymbol* symbol);
    cSymbol* GetSymbol(string name);

private:
    std::unordered_map<string, cSymbol*> table;

};
