#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        // param is the first decl in this decls
        cDeclsNode(cDeclNode *decl) : cAstNode(), m_size(0), m_offset(0)
        {
            Insert(decl);
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            decl->CalculateSize();
            
            AddChild(decl);
            
            decl->SetOffset(m_offset);
            int adder = decl->GetSize();
            this->m_size += adder;
            
            while ((adder%4)) adder++;
            
            this->m_offset += adder;
        }

        // return a particular decl from the list
        cDeclNode* GetDecl(int index)
        {
            return static_cast<cDeclNode*>(GetChild(index));
        }

        virtual string NodeType() { return string("decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
 
        virtual string AttributesToString()
        {
            string result(" size=\"");
            result += std::to_string(this->m_size) + "\"";
            return result;
        }
        
        int GetSize() { return this->m_size; }
        
protected:
        int m_size;
        int m_offset;
};
