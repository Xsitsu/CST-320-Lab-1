//**************************************
// cSymbolTable
//
// Implementation of Symbol Table
// NOTE: Most of the implementation is in the .h file.
// This function needs to be here to avoid circular includes
//
// Author: Phil Howard
// phil.howard@oit.edu
//
// Date: Feb. 10, 2017
//
//

#include "cSymbolTable.h"
#include "cBaseTypeNode.h"

// Add symbols for base types
void cSymbolTable::InitRootTable()
{
    cSymbol *type;

    type = new cSymbol("char");
    type->SetDecl(new cBaseTypeNode("char", 1, false));
    Insert(type);

    type = new cSymbol("int");
    type->SetDecl(new cBaseTypeNode("int", sizeof(int), false));
    Insert(type);

    type = new cSymbol("float");
    type->SetDecl(new cBaseTypeNode("float", sizeof(double), true));
    Insert(type);
}

// Global Symbol Table
cSymbolTable g_SymbolTable;
