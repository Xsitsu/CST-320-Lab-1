#pragma once
//**************************************
// cAssignNode.h
//
// Defines AST node for assignment statments
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"
#include "cVarExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        // params are the lval and the expression
        cAssignNode(cVarExprNode *lval, cExprNode *expr)
            : cStmtNode()
        {
            AddChild(lval);
            AddChild(expr);
        }

        cVarExprNode *GetLVal() 
        { 
            return static_cast<cVarExprNode*>(GetChild(0));
        }

        cExprNode *GetExpr() 
        { 
            return static_cast<cExprNode*>(GetChild(1));
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
