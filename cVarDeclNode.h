#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"

class cVarDeclNode : public cDeclNode
{
    public:
        cVarDeclNode(cSymbol*& symbol, cSymbol*& symbol2) : cDeclNode()
        {
            this->AddChild(symbol);
            this->AddChild(symbol2);
            
            symbol2->SetDecl(this);
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
