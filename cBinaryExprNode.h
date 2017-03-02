#pragma once
//**************************************
// cBinaryExprNode.h
//
// Defines AST node for binary expressions.
// Inherits from cExprNode
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cExprNode.h"
#include "cOpNode.h"

class cBinaryExprNode : public cExprNode
{
    public:
        // params are the left and right expressions and the operation.
        // The operation is a char: '+', '-', etc.
        cBinaryExprNode(cExprNode *left, int op, cExprNode *right)
            : cExprNode()
        {
            AddChild(left);
            AddChild(new cOpNode(op));
            AddChild(right);
        }

        // return the resulting type of the operation
        // performs operand promotion of numeric types
        virtual cDeclNode *GetType()
        {
            cDeclNode *left;
            cDeclNode *right;

            left = GetLeft()->GetType();
            right = GetRight()->GetType();

            if (left == nullptr || right == nullptr) 
            {
                SetHasError();
                return nullptr;
            }
            if (!left->IsNumeric() || !right->IsNumeric())
            {
                SetHasError();
                return nullptr;
            }

            if (left == right) 
                return left;
            else if (left->IsFloat())
                return left;
            else if (right->IsFloat())
                return right;
            else if (left->IsInt())
                return left;
            else if (right->IsInt())
                return right;
            else
                return left;    // should never get here
        }

        cExprNode* GetLeft()
        {
            return static_cast<cExprNode*>(GetChild(0));
        }

        cExprNode* GetRight()
        {
            return static_cast<cExprNode*>(GetChild(2));
        }

        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
