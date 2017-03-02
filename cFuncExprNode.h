#pragma once
//**************************************
// cFuncExprNode.h
//
// Defines AST node for function calls
//
// Inherits from cExprNode so that functions can be used in expressions
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cStmtsNode.h"
#include "cParamListNode.h"
#include "cExprNode.h"

class cFuncExprNode : public cExprNode
{
    public:
        // params are the symbol for the func decl, and the params
        cFuncExprNode(cSymbol *name, cParamListNode *params)
            : cExprNode()
        {
            AddChild(name);
            AddChild(params);
        }

        cSymbol* GetName() { return static_cast<cSymbol*>(GetChild(0)); }

        cDeclNode* GetType() { return GetName()->GetDecl()->GetType(); }

        cParamListNode *GetParams()
        {
            return static_cast<cParamListNode*>(GetChild(1));
        }

        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
