#pragma once

#include "cVisitor.h"
#include "cSymbolTable.h"

class cSizeOffset : public cVisitor
{
public:
    cSizeOffset() : cVisitor(), max_size(0), size_count(0), offset(0)
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
        if (node_size > 1)
        {
            while (this->offset % 4)
            {
                this->offset++;
                this->size_count++;
            }
        }
        
        node->SetOffset(this->offset);
        node->SetSize(node_size);
        
        this->offset += node_size;
        this->size_count += node_size;
    }
    
    
protected:
    int max_size;
    int size_count;
    int offset;
    
};

