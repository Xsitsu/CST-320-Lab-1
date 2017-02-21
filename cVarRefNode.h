#pragma once

#include "cAstNode.h"
#include "cExprNode.h"

class cVarRefNode : public cExprNode
{
public:
    cVarRefNode(cSymbol* symbol)
    {
        this->AddChild(symbol);
    }
    
    cVarRefNode(cSymbol* symbol, cSymbol* symbol2)
    {
        this->AddChild(symbol);
        this->AddChild(symbol2);
    }
    
    virtual string NodeType() { return string("varref"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
