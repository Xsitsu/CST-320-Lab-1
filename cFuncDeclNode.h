#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"

class cFuncDeclNode : public cDeclNode
{
public:
cFuncDeclNode(cSymbol* symbol, cSymbol* symbol2) : cDeclNode()
    {
        this->AddChild(symbol);
        this->AddChild(symbol2);
    }

    virtual string NodeType() { return string("func"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
