#pragma once

#include "cAstNode.h"
#include "cStmtNode.h"

class cIfNode : public cStmtNode
{
public:
    cIfNode(cExprNode* expr, cStmtsNode* stmts)
    {
        this->AddChild(expr);
        this->AddChild(stmts);
    }

    cIfNode(cExprNode* expr, cStmtsNode* stmts, cStmtsNode* stmts2)
    {
        this->AddChild(expr);
        this->AddChild(stmts);
        this->AddChild(stmts2);
    }
    
    virtual string NodeType() { return string("if"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
