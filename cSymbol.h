#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent symbols.
// Later labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Feb. 11, 2017
//

#include <string>

using std::string;

#include "cAstNode.h"
#include "cDeclNode.h"

class cSymbol : public cAstNode
{
    public:
        // param is name of symbol
        cSymbol(string name) : cAstNode()
        {
            m_id = ++nextId;        // get next available ID
            m_name = name;
            m_decl = nullptr;
        }

        // return name of symbol
        string GetName() { return m_name; }
        
        // Get/Set the decl associated with this symbol
        cDeclNode *GetDecl() { return m_decl; }
        void SetDecl(cDeclNode *decl) { m_decl = decl; }

        // return attributes for ToString()
        virtual string AttributesToString()
        {
            string result(" id=\"");
            result += std::to_string(m_id) + "\"";
            result += " name=\"" + m_name + "\"";
            if (m_decl != nullptr)
            {
                result += " decl=\"" + std::to_string(m_decl->GetName()->m_id);
                result +=  "\"";
            }
            return result;
        }

        // Node type for ToString()
        virtual string NodeType() { return string("sym"); }

        // standard visitor
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        static long long nextId;        // Next avail symbol ID
        long long m_id;                 // Unique ID for this symbol
        string m_name;                  // name of symbol
        cDeclNode *m_decl;              // declaration of this symbol
};
