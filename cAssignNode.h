#pragma once

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cVarRefNode.h"

class cAssignNode : public cStmtNode
{
public:
    cAssignNode(cVarRefNode* ref, cExprNode* expr)
    {
        this->AddChild(ref);
        this->AddChild(expr);
    }
    
    virtual string NodeType() { return string("assign"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
};
