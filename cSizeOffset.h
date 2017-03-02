#pragma once

#include "cVisitor.h"
#include "cSymbolTable.h"

class cSizeOffset : public cVisitor
{
public:
    cSizeOffset() : cVisitor(), max_size(0), size_count(0), offset_add_dir(1), offset(0), var_ref_size_count(0)
    {
        
    }
    
    void VisitAllNodes(cAstNode* node) { node->Visit(this); }
    
    void Visit(cBlockNode* node)
    {
        int offset = this->offset;
        int size_count = this->size_count;
        int max_size = this->max_size;
        
        this->max_size = 0;
        this->size_count = 0;
        
        this->VisitAllChildren(node);
        
        int size = this->size_count + this->max_size;
        node->SetSize(size);
        
        if (size > max_size)
        {
            this->max_size = size;
        }
        else
        {
            this->max_size = max_size;
        }
        
        this->offset = offset;
        this->size_count = size_count;
    }
    
    void Visit(cDeclsNode* node)
    {
        this->VisitAllChildren(node);
        node->SetSize(this->size_count);
    }
    
    void Visit(cVarDeclNode* node)
    {
        int node_size = node->GetType()->Sizeof();
        if (node_size > 1 || this->offset_add_dir < 0)
        {
            while (this->offset % 4)
            {
                this->offset += this->offset_add_dir;
                this->size_count++;
            }
        }
        
        node->SetOffset(this->offset);
        node->SetSize(node_size);
        
        this->offset += this->offset_add_dir * node_size;
        this->size_count += node_size;
    }
    
    void Visit(cFuncDeclNode* node)
    {
        int max_size = this->max_size;
        int size_count = this->size_count;
        int offset = this->offset;
        
        this->max_size = 0;
        this->size_count = 0;
        this->offset = 0;
        
        this->VisitAllChildren(node);
        int size = this->size_count + this->max_size;
        while (size % 4) size++;
        node->SetSize(size);
        
        this->max_size = max_size;
        this->size_count = size_count;
        this->offset = offset;
    }
    
    void Visit(cParamsNode* node)
    {
        int max_size = this->max_size;
        int size_count = this->size_count;
        int offset = this->offset;
        
        this->offset_add_dir = -1;
        
        this->max_size = 0;
        this->size_count = 0;
        this->offset = -12;
        
        this->VisitAllChildren(node);
        int size = this->size_count;
        while (size % 4) size++;
        node->SetSize(size);
        
        this->offset_add_dir = 1;
        
        this->max_size = max_size;
        this->size_count = size_count;
        this->offset = offset;
    }
    
    void Visit(cParamListNode* node)
    {
        this->var_ref_size_count = 0;
        
        this->VisitAllChildren(node);
        node->SetSize(this->var_ref_size_count);
    }
    
    void Visit(cVarExprNode* node)
    {
        this->var_ref_size_count += node->GetSize();
    }
    
protected:
    int max_size;
    int size_count;
    int offset_add_dir;
    int offset;
    int var_ref_size_count;
    
};

