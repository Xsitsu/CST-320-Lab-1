#pragma once

#include "cAstNode.h"

class cParamsNode : public cAstNode
{
public:
    cParamsNode( cAstNode* node)
    {
        this->AddChild(node);
    }
    
    virtual string NodeType() { return string("args"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
};
