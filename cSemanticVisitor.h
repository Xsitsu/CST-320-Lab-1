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
    
    virtual void Visit(cFuncCallNode* node)
    {
        cSymbol* name = node->GetName();
        if (name->GetDecl())
        {
            if (!name->GetDecl()->IsFunc())
            {
                std::string err;
                err += name->GetName();
                err += " is not a function";
                this->SemanticError(node, err);
            }
            else
            {
                cFuncDeclNode* decl_node = node->GetFuncDeclNode();
                if (!decl_node->GetStmts())
                {
                    std::string err = "Function ";
                    err += name->GetName();
                    err += " is not fully defined";
                    this->SemanticError(node, err);
                }
                else
                {
                    cParamsNode* params = decl_node->GetParams();
                    cParamsListNode* params_list = node->GetParams();
                    
                    if (params || params_list)
                    {
                        if ((!params || !params_list) || 
                            (params->NumParams() != params_list->NumParams()))
                        {
                            std::string err;
                            err += name->GetName();
                            err += " called with wrong number of arguments";
                            this->SemanticError(node, err);
                        }
                        else
                        {
                            for (int i = 0; i < params->NumParams(); i++)
                            {
                                cVarDeclNode* param = params->GetParam(i);
                                cExprNode* passed_param = params_list->GetParam(i);
                                if (param->GetType() != passed_param->GetUltimateType())
                                {
                                    std::string err;
                                    err += name->GetName();
                                    err += " called with incompatible argument";
                                    this->SemanticError(node, err);
                                    break;
                                }
                            }
                        }
                    }   
                }
            }
        }
        else
        {
            std::string err = "Function ";
            err += name->GetName();
            err += " is not declared";
            this->SemanticError(node, err);
        }
        
        VisitAllChildren(node);
    }
    
    
};
