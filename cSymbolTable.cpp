#include "cSymbolTable.h"

void cSymbolTable::InsertSymbol(cSymbol* symbol)
{
    string name = symbol->GetName();
    table[name] = symbol;
}

cSymbol* cSymbolTable::GetSymbol(string name)
{
    cSymbol* ptr = nullptr;
    ptr = table[name];
    return ptr;
}

