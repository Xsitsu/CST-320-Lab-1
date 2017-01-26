#pragma once

#include "cSymbol.h"
#include "cSymbolTable.h"

void IncreaseScope();
void DecreaseScope();

cSymbol* Insert(char* yytext);
