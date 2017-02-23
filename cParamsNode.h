#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cVarDeclNode.h"

class cParamsNode : public cAstNode
{
public:
    cParamsNode(cDeclNode* decl)
    {
        this->AddChild(decl);
    }
    
    virtual string NodeType() { return string("args"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
    cVarDeclNode* GetParam(int num)
    {
        return static_cast<cVarDeclNode*>(this->GetChild(num));
    }
    
};
