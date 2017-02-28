#pragma once

#include "cExprNode.h"
#include "cParamsListNode.h"

class cFuncCallNode : public cExprNode
{
public:
    cFuncCallNode(cSymbol* name)
    {
        this->AddChild(name);
    }
    cFuncCallNode(cSymbol* name, cParamsListNode* params)
    {
        this->AddChild(name);
        this->AddChild(params);
    }
    
    cSymbol* GetName()
    {
        return static_cast<cSymbol*>(this->GetChild(0));
    }
    
    virtual cDeclNode* GetType()
    {
        return this->GetName()->GetDecl()->GetType();
    }
    
    cFuncDeclNode* GetFuncDeclNode()
    {
        cSymbol* name = this->GetName();
        if (name->GetDecl() && name->GetDecl()->IsFunc())
        {
            return static_cast<cFuncDeclNode*>(name->GetDecl());
        }
        else
        {
            return nullptr;
        }
    }
    
    virtual string NodeType() { return string("funcCall"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
};
