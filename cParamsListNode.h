#pragma once

#include "cAstNode.h"
#include "cExprNode.h"

class cParamsListNode : public cAstNode
{
public:
    cParamsListNode(cExprNode* expr)
    {
        this->AddChild(expr);
    }
    
    virtual string NodeType() { return string("params"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
    cExprNode* GetParam(int num)
    {
        return static_cast<cExprNode*>(this->GetChild(num));
    }
    
    int NumParams()
    {
        return this->NumChildren();
    }
    
};
