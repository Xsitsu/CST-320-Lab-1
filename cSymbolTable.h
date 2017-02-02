#pragma once
//**************************************
// cSymbolTable.h
//
// Defines a nested symbol table.
// Individual levels of the symbol table use a std::unordered_map from the STL
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 26, 2016
//

#include <string>
#include <unordered_map>
#include <list>
#include <utility>      // use pair

using std::string;
using std::unordered_map;
using std::list;
using std::pair;

#include "cSymbol.h"

class cSymbolTable
{
    public:
        // Type for a single symbol table
        typedef unordered_map<string, cSymbol *> symbolTable_t;

        // Increasing the scope must create a symbol table, so we call
        // that function to do the actual work of creating the object
        cSymbolTable()
        { 
            IncreaseScope();
        }

        // Increase the scope: add a level to the nested symbol table
        // Return value is the newly created scope
        symbolTable_t *IncreaseScope()
        {
            symbolTable_t *table = new symbolTable_t();
            m_SymbolTable.push_front(table);

            return table;
        }

        // Decrease the scope: remove the outer-most scope.
        // Returned value is the outer-most scope AFTER the pop.
        //
        // NOTE: do NOT clean up memory after poping the table. Parts of the
        // AST will probably contain pointers to symbols in the popped table.
        symbolTable_t *DecreaseScope()
        {
            m_SymbolTable.pop_front();

            return m_SymbolTable.front();
        }

        // insert a symbol into the table
        // Assumes the symbol is not already in the table
        void Insert(cSymbol *sym)
        {
            pair<string, cSymbol*> new_val(sym->GetName(), sym);
            m_SymbolTable.front()->insert(new_val);
        }

        // Do a lookup in the nested table. Return the symbol for the outer-most
        // match. 
        // Returns nullptr if no match is found.
        cSymbol *Find(string name)
        {
            cSymbol *sym = nullptr;

            list<symbolTable_t *>::iterator it = m_SymbolTable.begin();

            while (it != m_SymbolTable.end())
            {
                sym = FindInTable(*it, name);
                if (sym != nullptr) return sym;

                it++;
            }

            return nullptr;
        }

        // Find a symbol in the inner-most scope.
        // Returns nullptr if the symbol is not found.
        cSymbol *FindLocal(string name)
        {
            return FindInTable(m_SymbolTable.front(), name);
        }

    protected:
        // list of symbol tables. The list contains the different levels
        // in the nested table.
        list<symbolTable_t *> m_SymbolTable;

        // Utility routine to do a lookup in a single level's table
        // params are the table to do the lookup in and the name of the symbol
        // Returns nullptr if the symbol isn't found.
        cSymbol *FindInTable(symbolTable_t *table, string& name)
        {
            symbolTable_t::const_iterator got = table->find(name);

            if (got == table->end())
                return nullptr;
            else
                return got->second;
        }

};

// Declaration for the global symbol table.
// Definition is in main.cpp
extern cSymbolTable g_SymbolTable;
