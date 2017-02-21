#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"

class cFuncDeclNode : public cDeclNode
{
public:
cFuncDeclNode(cSymbol* symbol, cSymbol* symbol2) : cDeclNode()
    {
        this->AddChild(symbol);
        this->AddChild(symbol2);
    
        symbol2->SetDecl(this);
    }

    virtual string NodeType() { return string("func"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    virtual cSymbol* GetName()
    {
        return static_cast<cSymbol*>(this->GetChild(1));
    }

    virtual cDeclNode* GetType()
    {
        return static_cast<cSymbol*>(this->GetChild(0))->GetDecl();
    }
    
    virtual bool IsFunc() { return true; }
    
};
