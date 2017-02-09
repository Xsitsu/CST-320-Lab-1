#pragma once

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"

class cWhileNode : public cStmtNode
{
public:
    cWhileNode(cExprNode* expr, cStmtNode* stmt)
    {
        this->AddChild(expr);
        this->AddChild(stmt);
    }
    
    virtual string NodeType() { return string("while"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
};
