#pragma once
//**************************************
// cIntExprNode.h
//
// Defines an AST node for an integer constant (literals).
//
// Inherits from cExprNode so that integer constants can be used anywhere 
// expressions are used.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cAstNode.h"
#include "cExprNode.h"

class cIntExprNode : public cExprNode
{
    public:
        // param is the value of the integer constant
        cIntExprNode(int value) : cExprNode()
        {
            m_value = value;
        }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("int"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        
        virtual cDeclNode* GetType()
        {
            cSymbol* symbol;
            if (m_value >= -128 && m_value <= 127)
            {
                symbol = g_SymbolTable.Find("char");
            }
            else
            {
                symbol = g_SymbolTable.Find("int");
            }

            return symbol->GetDecl();

        }

        
protected:
        int m_value;        // value of integer constant (literal)
};
