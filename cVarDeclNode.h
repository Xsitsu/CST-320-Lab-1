#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"

class cVarDeclNode : public cDeclNode
{
    public:
        cVarDeclNode(cSymbol* type, cSymbol* id) : cDeclNode()
        {
            if (!g_SymbolTable.FindLocal(id->GetName()))
            {
                if (g_SymbolTable.Find(id->GetName()))
                {
                    id = new cSymbol(id->GetName());
                }
                
                g_SymbolTable.Insert(id);
            }
            else
            {
                string err = "Symbol ";
                err += id->GetName();
                err += " already defined in current scope";
                SemanticError(err);
            }
            
            this->AddChild(type);
            this->AddChild(id);
            
            id->SetDecl(this);
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        
        virtual cSymbol* GetName()
        {
            return static_cast<cSymbol*>(this->GetChild(1));
        }
        
        virtual cDeclNode* GetType()
        {
            return static_cast<cSymbol*>(this->GetChild(0))->GetDecl();
        }
        
        virtual bool IsVar() { return true; }
        
    protected:
        int m_value;        // value of integer constant (literal)
};
