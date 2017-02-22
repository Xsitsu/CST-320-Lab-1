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

        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        int m_value;        // value of integer constant (literal)
};
