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
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        int m_value;        // value of integer constant (literal)
};
