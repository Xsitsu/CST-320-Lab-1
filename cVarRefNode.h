#pragma once

#include <iostream>

#include "cAstNode.h"
#include "cExprNode.h"

class cVarRefNode : public cExprNode
{
public:
    cVarRefNode(cSymbol* name)
    {
        this->AddChild(name);
        this->number_array_indexes = 0;
    }
    
    void AddArrayIndex(cExprNode* index)
    {
        this->AddChild(index);
        this->number_array_indexes++;
    }
    
    int NumArrayIndexes() { return this->number_array_indexes; }
    
    cExprNode* GetArrayIndex(int num)
    {
        if (num >= 0 && num < this->number_array_indexes)
        {
            return static_cast<cExprNode*>(this->GetChild(num+1));
        }
        return nullptr;
    }
    
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
    
    virtual cDeclNode* GetUltimateType()
    {
        cDeclNode* decl = this->GetName()->GetDecl();
        
        int num_indexes = this->NumArrayIndexes();
        cDeclNode* type = decl->GetType();
        bool did_error = false;
        int index = 0;
        while (!did_error && index < num_indexes)
        {
            if (type->IsArray())
            {
                type = type->GetType();
            }
            else
            {
                did_error = true;
            }

            index++;
        }
        
        if (did_error)
        {
            return nullptr;
        }
        
        return type;

    }
    
    
    virtual string NodeType() { return string("varref"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
protected:
    int number_array_indexes;

};
