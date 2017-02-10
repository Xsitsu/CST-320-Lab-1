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
protected:
    int m_size;
    
};
