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
        else
        {
            int num_indexes = node->NumArrayIndexes();
            cDeclNode* type = decl->GetType();
            bool did_error = false;
            int index = 0;
            while (!did_error && index < num_indexes)
            {
                if (type->IsArray())
                {
                    cExprNode* index_node = node->GetArrayIndex(index);
                    cDeclNode* index_type = index_node->GetUltimateType();
                    
                    if (!index_type->IsInt() && !index_type->IsChar())
                    {
                        did_error = true;
                        
                        std::string err = "Index of ";
                        err += node->GetName()->GetName();
                        err += " is not an int";
                        this->SemanticError(node, err);
                    }
                    
                    type = type->GetType();
                }
                else
                {
                    did_error = true;
                    
                    std::string err;
                    err += type->GetName()->GetName();
                    err += " is not an array";
                    this->SemanticError(node, err);
                }
                
                index++;
            }
        }
        
        VisitAllChildren(node);
    }
    
    virtual void Visit(cAssignNode* node)
    {
        cDeclNode* lval_type = node->GetLval()->GetUltimateType();
        cDeclNode* expr_type = node->GetExpr()->GetUltimateType();
        
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
