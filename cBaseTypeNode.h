#pragma once

#include "cAstNode.h"
#include "cSymbol.h"

class cBaseTypeNode : public cDeclNode
{
public:
cBaseTypeNode(cSymbol* symbol, int which) : cDeclNode()
    {
        m_symbol = symbol;
        m_which = which;
        
        symbol->SetDecl(this);
    }

    virtual bool IsType() { return true; }
    
    virtual bool IsChar()
    {
        return m_which == 1;
    }

    virtual bool IsInt()
    {
        return m_which == 2;
    }

    virtual bool IsFloat()
    {
        return m_which == 3;
    }
    
    virtual cDeclNode* GetType() { return this; }
    
    virtual string NodeType() { return "base_type"; }
    virtual void Visit(cVisitor* visitor) { visitor->Visit(this); }
    
    virtual cSymbol* GetName() { return m_symbol; }
    
private:
    cSymbol* m_symbol;
    int m_which;
    
};
