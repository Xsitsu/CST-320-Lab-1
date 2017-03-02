#pragma once
//**************************************
// cArrayDeclNode.h
//
// Defines AST node for a array declaration
//
// Inherits from cDeclNode because this is a type of declaration
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

class cArrayDeclNode : public cDeclNode
{
    public:
        // params are: 
        //     the name of the base type for this array
        //     the cSymbol for the name of the array
        //     the size of the array
        cArrayDeclNode( cSymbol *type_id,
                        cSymbol *array_id,
                        int size)
            : cDeclNode()
        {
            cSymbol *name;

            AddChild(type_id);

            // Figure out if the ID we were passed already exists in the 
            // local symbol table. 
            name = g_SymbolTable.FindLocal(array_id->GetName());
            if (name == nullptr)
            {
                // No: this is good. A later lab will cause an error if it does
                name = array_id;

                // If the symbol exists in an outer scope, we need to create
                // a new one instead of re-using the symbol from the outer scope
                if (g_SymbolTable.Find(array_id->GetName()) != nullptr)
                {
                    name = new cSymbol(array_id->GetName());
                }

                name->SetDecl(this);

                // insert the name of the array into the global symbol table
                g_SymbolTable.Insert(name);
            }

            AddChild(name);

            m_count = size;
        }

        // return the type of the elements
        virtual cDeclNode *GetBaseType()
        {
            cSymbol* type = static_cast<cSymbol*>(GetChild(0));

            return type->GetDecl();
        }

        // Since this IS a type, return self
        virtual cDeclNode *GetType() { return this; }

        virtual cDeclNode *GetType(int depth) 
        { 
            if (depth == 0) return this;
            return GetBaseType()->GetType(depth - 1); 
        }

        virtual bool IsType()   { return true; }
        virtual bool IsArray()  { return true; }

        virtual cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(1));
        }

        virtual string NodeType() { return string("array_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual string AttributesToString()
        {
            return " count=\"" + std::to_string(m_count) + "\"";
        }
    protected:
        int m_count;

};
