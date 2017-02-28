#pragma once

#include "cAstNode.h"
#include "cExprNode.h"

class cVarRefNode : public cExprNode
{
public:
    cVarRefNode(cSymbol* name)
    {
        this->AddChild(name);
    }
    
    /*
    cVarRefNode(cSymbol* symbol, cSymbol* symbol2)
    {
        this->AddChild(symbol);
        this->AddChild(symbol2);
    }
    */
    
    cSymbol* GetName()
    {
        return static_cast<cSymbol*>(this->GetChild(0));
    }
    
    virtual cDeclNode* GetType()
    {
        cSymbol* name = this->GetName();
        if (name->GetDecl())
        {
            return name->GetDecl()->GetType();
        }
        else
        {
            return nullptr;
        }
    }
    
    virtual string NodeType() { return string("varref"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
