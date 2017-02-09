#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"

class cStructDeclNode : public cDeclNode
{
    public:
        cStructDeclNode(cDeclsNode* decls, cSymbol* symbol) : cDeclNode()
        {
            this->AddChild(decls);
            this->AddChild(symbol);
        }

        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
