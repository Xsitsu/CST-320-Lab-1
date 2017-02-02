#include "cSymbolTable.h"

cSymbol* cSymbolTable::InsertSymbol(char* yytext)
{
    symbtbl* useTable = &tableList.back();
    
    std::string name;
    name += yytext;
    
    cSymbol* symbol = (*useTable)[name];
    if (symbol == nullptr)
    {
        symbol = new cSymbol(name);
        (*useTable)[name] = symbol;
    }
    
    return symbol;
}

void cSymbolTable::IncreaseScope()
{
    tableList.push_back(symbtbl());
}

void cSymbolTable::DecreaseScope()
{
    tableList.pop_back();
}
