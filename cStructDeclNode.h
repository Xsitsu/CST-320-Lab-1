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
        
        symbol->SetDecl(this);
    }
    
    virtual string NodeType() { return string("struct_decl"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
    virtual cSymbol* GetName()
    {
        return static_cast<cSymbol*>(this->GetChild(1));
    }
    
    virtual cDeclNode* GetType()
    {
        return static_cast<cSymbol*>(this->GetChild(0))->GetDecl();
    }
    
    virtual bool IsStruct() { return true; }
    virtual bool IsType() { return true; }
    
};
