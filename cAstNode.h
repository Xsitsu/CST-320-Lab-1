#pragma once
//**************************************
// cAstNode.h
//
// pure virtual base class for all AST nodes
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "cVisitor.h"

// should come from include file, but that causes dependency problems
extern int yylineno;

// called to throw a semantic error
extern void SemanticError(std::string error);

class cAstNode
{
    public:
        // iterator for going through the children
        typedef vector<cAstNode*>::iterator iterator;

        cAstNode() 
        {
            m_lineNumber = yylineno;
            m_hasSemanticError = false;
        }

        void AddChild(cAstNode *child)
        {
            m_children.push_back(child);
        }

        iterator FirstChild()
        {
            return m_children.begin();
        }

        iterator LastChild()
        {
            return m_children.end();
        }

        bool HasChildren()      { return !m_children.empty(); }
        int NumChildren()       { return (int)m_children.size(); }

        cAstNode* GetChild(int child)
        {
            if (child >= (int)m_children.size()) return nullptr;
            return m_children[child];
        }

        void SetHasError() { m_hasSemanticError = true; }
        bool HasError()    { return m_hasSemanticError; }

        // return a string representation of the node
        // The recurses through the whole AST
        // This should NOT be overridden in subclasses
        string ToString() 
        {
            string result("");

            result += "<" + NodeType();
            result += AttributesToString();

            if (HasChildren())
            {
                result += ">";
                iterator it;
                for (it=FirstChild(); it != LastChild(); it++)
                {
                    if ( (*it) != nullptr) result += (*it)->ToString();
                }
            }

            if (HasChildren()) 
                result += "</" + NodeType() + ">\n";
            else
                result += "/>";

            return result;
        }

        int LineNumber() { return m_lineNumber; }

        // AttributesToString must be overriden by subclasses
        // that have attributes.
        virtual string AttributesToString()   { return string(""); }
        virtual string NodeType() = 0; //      { return "AST"; }
        virtual void Visit(cVisitor *visitor) = 0;

    protected:
        vector<cAstNode *> m_children;     // list of statements
        int m_lineNumber;
        bool m_hasSemanticError;
};

