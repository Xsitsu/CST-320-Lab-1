#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"

class cFuncDeclNode : public cDeclNode
{
private:
cFuncDeclNode(cSymbol* type, cSymbol* id) : cDeclNode()
    {
        this->AddChild(type);
        this->AddChild(id);
    
        id->SetDecl(this);
    }

public:
    static cFuncDeclNode* Make(cSymbol* type, cSymbol* id)
    {
        if (!g_SymbolTable.FindLocal(id->GetName()))
        {
            if(g_SymbolTable.Find(id->GetName()))
            {
                id = new cSymbol(id->GetName());
            }
            
            g_SymbolTable.Insert(id);
        }
        
        cDeclNode* old = g_SymbolTable.Find(id->GetName())->GetDecl();
        if (old)
        {
            if (old->IsFunc() && old->GetType() == type->GetDecl())
            {
                cSymbol* t = old->GetType()->GetName();
                cSymbol* i = old->GetName();
                return new cFuncDeclNode(t, i);
                //return static_cast<cFuncDeclNode*>(old);
            }
        }
        
        return new cFuncDeclNode(type, id);
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
