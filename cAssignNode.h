#pragma once

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cVarRefNode.h"

class cAssignNode : public cStmtNode
{
public:
    cAssignNode(cVarRefNode* lval, cExprNode* expr)
    {
        this->AddChild(lval);
        this->AddChild(expr);
    }
    
    cVarRefNode* GetLval() { return static_cast<cVarRefNode*>(this->GetChild(0)); }
    cExprNode* GetExpr() { return static_cast<cExprNode*>(this->GetChild(1)); }
    
    virtual string NodeType() { return string("assign"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
};
