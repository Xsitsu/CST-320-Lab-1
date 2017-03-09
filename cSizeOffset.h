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
    
    void Visit(cProgramNode* node)
    {
        this->VisitAllChildren(node);
        
        cBlockNode* block = node->GetBlock();
        int size = block->GetSize();
        while (size % 4) size++;
        block->SetSize(size);
    }
    
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
        int calc_size = node_size;
        
        if (this->offset_add_dir > 0)
        {
            if (node_size > 1)
            {
                while (this->offset % 4)
                {
                    this->offset++;
                    this->size_count++;
                }
            }
            
            node->SetOffset(this->offset);
            
            this->offset += node_size;
            this->size_count += node_size;
        }
        else if (this->offset_add_dir < 0)
        {
            if (calc_size < 4)
                calc_size = 4;
            
            this->offset -= calc_size;
            node->SetOffset(this->offset);
            this->size_count += calc_size;
        }
        
        node->SetSize(node_size);
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
        this->offset = -8;
        
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

