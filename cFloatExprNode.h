#pragma once
//**************************************
// cFloatExprNode.h
//
// Defines an AST node for a float constant (literals).
//
// Inherits from cExprNode so that float constants can be used anywhere 
// expressions are used.
//
//

#include "cAstNode.h"
#include "cExprNode.h"

class cFloatExprNode : public cExprNode
{
    public:
        // param is the value of the integer constant
        cFloatExprNode(double value) : cExprNode()
        {
            m_value = value;
        }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("float"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        double m_value;        // value of float constant (literal)
};
