#pragma once

#include "cAstNode.h"
#include "cExprNode.h"
#include "cOpNode.h"

class cMathExprNode : public cExprNode
{
public:
cMathExprNode(cExprNode* lhs, cOpNode* op, cExprNode* rhs) : cExprNode()
    {
        this->AddChild(lhs);
        this->AddChild(op);
        this->AddChild(rhs);
    }
    
    cExprNode* GetLHS() { return static_cast<cExprNode*>(this->GetChild(0)); }
    cOpNode* GetOp() { return static_cast<cOpNode*>(this->GetChild(1)); }
    cExprNode* GetRHS() { return static_cast<cExprNode*>(this->GetChild(2)); }
    
    virtual cDeclNode* GetType()
    {
        cDeclNode* lhs_type = this->GetLHS()->GetType();
        cDeclNode* rhs_type = this->GetRHS()->GetType();
        
        return lhs_type;
    }
    
    virtual string NodeType() { return string("expr"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
protected:

};
