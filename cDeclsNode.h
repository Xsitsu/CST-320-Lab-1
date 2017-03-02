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
        cDeclsNode(cDeclNode *decl) : cAstNode(), m_size(0)
        {
            Insert(decl);
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
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
            if (this->m_size < 1) return "";
            
            string result(" size=\"");
            result += std::to_string(this->m_size) + "\"";
            return result;
        }
        
        int GetSize() { return this->m_size; }
        void SetSize(int size) { this->m_size = size; }
        
protected:
        int m_size;
};
