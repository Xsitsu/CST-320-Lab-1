#pragma once

#include <string>

#include "cVisitor.h"

using std::string;

class cSemanticVisitor : public cVisitor
{
protected:
    int m_numErrors;
    
public:
    cSemanticVisitor()
    {
        m_numErrors = 0;
    }
    
    int NumErrors() { return this->m_numErrors; }
    
    void SemanticError(cAstNode* node, string msg)
    {
        m_numErrors++;
        
        node->SetHasError();
        std::cout << "ERROR: " << msg << 
            " on line " << node->LineNumber() << "\n";
    }
    
    void VisitAllNodes(cAstNode* node)
    {
        node->Visit(this);
    }
    
    
    virtual void Visit(cVarRefNode* node)
    {
        cDeclNode* decl = node->GetName()->GetDecl();
        if (!decl)
        {
            std::string err = "Symbol ";
            err += node->GetName()->GetName();
            err += " not defined";
            this->SemanticError(node, err);
        }
        
        VisitAllChildren(node);
    }
    
    virtual void Visit(cAssignNode* node)
    {
        cDeclNode* lval_type = node->GetLval()->GetType();
        cDeclNode* expr_type = node->GetExpr()->GetType();
        
        if (lval_type && expr_type)
        {
            if (lval_type != expr_type)
            {
                bool is_okay = (lval_type->IsInt() && expr_type->IsChar());
                if (!is_okay)
                {
                    std::string err = "Cannot assign ";
                    err += expr_type->GetName()->GetName();
                    err += " to ";
                    err += lval_type->GetName()->GetName();
                    this->SemanticError(node, err);
                }
            }
        }
        
        VisitAllChildren(node);
    }
  
};
