#pragma once
//**************************************
// cReturnNode.h
//
// Defines AST node for a lang return statement
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Feb. 18, 2017
//


#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"

class cReturnNode : public cStmtNode
{
    public:
        cReturnNode(cExprNode *expr)
        {
            AddChild(expr);
        }

        virtual string NodeType() { return string("return"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
