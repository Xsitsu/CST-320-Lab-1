#pragma once
//**************************************
// cParamsNode.h
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

class cParamsNode : public cDeclsNode
{
    public:
        // param is the first decl in this decls
        cParamsNode(cDeclNode *decl) : cDeclsNode(decl)
        {
            // child is added in base constructor
        }

        // return the XML node name
        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
