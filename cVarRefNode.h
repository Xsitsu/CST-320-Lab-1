#pragma once

#include "cAstNode.h"
#include "cExprNode.h"

class cVarRefNode : public cExprNode
{
    public:
        // param is the value of the integer constant
        cVarRefNode(cAstNode* node)
        {
            this->AddChild(node);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
