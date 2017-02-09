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

        cVarRefNode(cAstNode* node, cAstNode* node2)
        {
            this->AddChild(node);
            this->AddChild(node2);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
