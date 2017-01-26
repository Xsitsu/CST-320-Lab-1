#include "cSymbolTableStack.h"

#include <string>

void IncreaseScope()
{
    
}

void DecreaseScope()
{
    
}

cSymbol* Insert(char* yytext)
{
    std::string str;
    str += yytext;
    cSymbol* symbol = new cSymbol(str);
    
    return symbol;
}
