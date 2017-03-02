#pragma once
//**************************************
// cVarDeclNode.h
//
// Defines AST node for a variable declaration
//
// Inherits from cDeclNode so variables can be added to lists of decls
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

class cVarDeclNode : public cDeclNode
{
    public:
        // params are the symbol for the type and the name
        cVarDeclNode(cSymbol *type_id, cSymbol *var_id)
        {
            AddChild(type_id);

            // Check to see if the symbol is not in the inner most scope.
            // If it is, this is an error
            cSymbol* m_var = g_SymbolTable.FindLocal(var_id->GetName());
            if (m_var == NULL)
            {
                m_var = var_id;

                // If the symbol exists in an outer scope, we need to create
                // a new one instead of reusing the outer scope's symbol.
                if (g_SymbolTable.Find(var_id->GetName()) != nullptr)
                {
                    m_var = new cSymbol(var_id->GetName());
                }

                // Insert into the global symbol table
                g_SymbolTable.Insert(m_var);
                //m_var->SetDecl(type_id->GetDecl());
                m_var->SetDecl(this);

                AddChild(m_var);
            }
            else
            {
                string error("");

                error += "Symbol " + m_var->GetName();
                error += " already defined in current scope";
                SetHasError();
                SemanticError(error);
            }
        }

        virtual bool IsVar()  { return true; }

        // return the type of the var
        virtual cDeclNode *GetType() 
        { 
            cSymbol* type = static_cast<cSymbol*>(GetChild(0));

            return type->GetDecl(); 
        }

        virtual cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(1));
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
