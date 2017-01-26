#include "cSymbolTableStack.h"

#include <string>
#include <list>

using std::string;

extern cSymbolTable g_SymbolTable;

std::list<cSymbolTable> tableList;

void IncreaseScope()
{
    tableList.push_back(cSymbolTable());
}

void DecreaseScope()
{
    tableList.pop_back();
}

cSymbol* Insert(char* yytext)
{
    cSymbolTable* useTable = &g_SymbolTable;
    
    if (!tableList.empty())
    {
        useTable = &tableList.back();
    }
    
    string name;
    name += yytext;
    
    cSymbol* symbol = useTable->GetSymbol(name);
    if (symbol == nullptr)
    {
        symbol = new cSymbol(name);
        useTable->InsertSymbol(symbol);
    }
    
    return symbol;
}
