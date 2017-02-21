#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"

class cArrayDeclNode : public cDeclNode
{
public:
    cArrayDeclNode(int size, cSymbol* type, cSymbol* name)
    {
        this->m_size = size;
        this->AddChild(type);
        this->AddChild(name);
        
        name->SetDecl(this);
    }
    
    virtual string AttributesToString()
    {
        string result(" count='");
        result += std::to_string(this->m_size);
        result += "'";
        return result;
    }
    
    virtual string NodeType() { return string("array_decl"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    virtual cSymbol* GetName()
    {
        return static_cast<cSymbol*>(this->GetChild(1));
    }

    virtual cDeclNode* GetType()
    {
        return static_cast<cSymbol*>(this->GetChild(0))->GetDecl();
    }
    
    virtual bool IsArray() { return true; }
    virtual bool IsType() { return true; }
    
protected:
    int m_size;
    
};
