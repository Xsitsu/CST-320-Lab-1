#pragma once

#include "cExprNode.h"
#include "cParamsListNode.h"

class cFuncCallNode : public cExprNode
{
public:
    cFuncCallNode(cSymbol* name)
    {
        this->AddChild(name);
    }
    cFuncCallNode(cSymbol* name, cParamsListNode* params)
    {
        this->AddChild(name);
        this->AddChild(params);
    }
    
    virtual string NodeType() { return string("funcCall"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
};
