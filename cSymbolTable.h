#pragma once

#include <unordered_map>
#include <list>

#include "cSymbol.h"

using std::string;

typedef std::unordered_map<string, cSymbol*> symbtbl;

class cSymbolTable
{
public:
    cSymbol* InsertSymbol(char* yytext);

    void IncreaseScope();
    void DecreaseScope();

private:
    std::list<symbtbl> tableList;

};
