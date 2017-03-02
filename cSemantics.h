#pragma once
//**************************************
// cSemantic.h 
//
// Defines visitor class for semantic processing
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Feb. 20, 2017
//

#include "cVisitor.h"
#include "cSymbolTable.h"

void FatalError(const char *msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

class cSemantics : public cVisitor
{
  public:
    cSemantics() : cVisitor()
    {
        m_numErrors = 0;
    }

    int NumErrors() { return m_numErrors; }

    void SemanticError(cAstNode *node, string msg)
    {
        m_numErrors++;

        node->SetHasError();
        std::cout << "ERROR: " << msg <<
            " on line " << node->LineNumber() << "\n";
    }

    void VisitAllNodes(cAstNode *node) { node->Visit(this); }

    //void Visit(cArrayRefNode *node)     { VisitAllChildren(node); }
    //void Visit(cAstNode *node)          { VisitAllChildren(node); }

    void Visit(cAssignNode *node)
    { 
        cVarExprNode* lval = node->GetLVal();
        cExprNode*    expr = node->GetExpr();

        VisitAllChildren(node);

        if (lval->HasError() || expr->HasError())
        {
            return; // var not defined: already reported
        }

        if (!lval->GetType()->IsCompatibleWith(expr->GetType()))
        {
            SemanticError(node, "Cannot assign " + 
                    expr->GetType()->GetName()->GetName() +
                    " to " + lval->GetType()->GetName()->GetName());
        }
    }

    void Visit(cBinaryExprNode *node)   
    { 
        VisitAllChildren(node); 

        if (node->GetLeft()->HasError() || node->GetRight()->HasError()) 
        {
            node->SetHasError();
        }
    }

    //void Visit(cBlockNode *node)        { VisitAllChildren(node); }
    //void Visit(cDeclNode *node)         { VisitAllChildren(node); }
    //void Visit(cDeclsNode *node)        { VisitAllChildren(node); }
    //void Visit(cExprNode *node)         { VisitAllChildren(node); }
    //void Visit(cFloatExprNode *node)    { VisitAllChildren(node); }
    //void Visit(cFuncDeclNode *node)     { VisitAllChildren(node); }
    void Visit(cFuncExprNode *node)     
    { 
        VisitAllChildren(node);
        if (node->HasError()) return;

        // defined?
        if (node->GetName()->GetDecl() == nullptr)
        {
            SemanticError(node, "Function " + node->GetName()->GetName() +
                    " is not declared");
            return;
        }

        // defined as a function?
        if (!node->GetName()->GetDecl()->IsFunc())
        {
            SemanticError(node, node->GetName()->GetName() +
                    " is not a function");
            return;
        }

        // definition has a body?
        cFuncDeclNode *decl = dynamic_cast<cFuncDeclNode*>
            (node->GetName()->GetDecl());
        if (decl == nullptr || !decl->IsFullyDefined())
        {
            SemanticError(node, node->GetName()->GetName() +
                    " is not fully defined");
        }

        // check for compatible params
        cParamListNode* args = node->GetParams();
        cDeclsNode*  formals = decl->GetParams();

        if ( (args == nullptr && formals != nullptr) ||
             (args != nullptr && formals == nullptr))
        {
            SemanticError(node, node->GetName()->GetName() +
                    " called with wrong number of arguments");
            return;
        }
        else if (args != nullptr && formals != nullptr)
        {
            if (args->NumChildren() != formals->NumChildren())
            {
                SemanticError(node, node->GetName()->GetName() +
                        " called with wrong number of arguments");
                return;
            }

            for (int ii=0; ii<args->NumChildren(); ii++)
            {
                if (!formals->GetDecl(ii)->GetType()->IsCompatibleWith(
                            args->GetParam(ii)->GetType()))
                {
                    SemanticError(node, node->GetName()->GetName() +
                            " called with incompatible argument");
                    return;
                }
            }
        }
    }

    //void Visit(cIfNode *node)           { VisitAllChildren(node); }
    //void Visit(cIntExprNode *node)      { VisitAllChildren(node); }
    //void Visit(cOpNode *node)           { VisitAllChildren(node); }
    //void Visit(cParamListNode *node)    { VisitAllChildren(node); }
    //void Visit(cParamsNode *node)       { VisitAllChildren(node); }
    //void Visit(cPrintNode *node)        { VisitAllChildren(node); }
    //void Visit(cReturnNode *node)       { VisitAllChildren(node); }
    //void Visit(cStmtNode *node)         { VisitAllChildren(node); }
    //void Visit(cStmtsNode *node)        { VisitAllChildren(node); }
    //void Visit(cStructDeclNode *node)   { VisitAllChildren(node); }
    //void Visit(cSymbol *node)           { VisitAllChildren(node); }
    //void Visit(cVarDeclNode *node)      { VisitAllChildren(node); }
    void Visit(cVarExprNode *node)      
    { 
        bool isStruct = false;
        bool isArray = false;

        // declared?
        if (node->GetName()->GetDecl() == nullptr)
        {
            SemanticError(node, "Symbol " + node->GetName()->GetName() + 
                    " not defined ");
        }

        VisitAllChildren(node); 
        if (node->HasError()) return;

        // check for valid indexing
        for (int ii=0; ii<node->NumItems(); ii++)
        {
            if (node->ItemIsIndex(ii))
            {
                isArray = true;
                if (isStruct)
                {
                    SemanticError(node, 
                            "Mixed arrays and structs not supported");
                    return;
                }

                // is the base an array?
                cDeclNode *itemDecl = node->GetName()->GetDecl()->GetType();
                if (!itemDecl->GetType(ii)->IsArray())
                {
                    SemanticError(node, node->GetTextName() + 
                            " is not an array");
                    return;
                }

                // is the index an int?
                if (!node->GetIndex(ii)->GetType()->IsIntegral())
                {
                    SemanticError(node, "Index of " + node->GetTextName() +
                            " is not an int");
                    return;
                }
            }
            else
            {
                isStruct = true;
                if (isArray)
                {
                    SemanticError(node, 
                            "Mixed arrays and structs not supported");
                    return;
                }
            }
        }

    }
    //void Visit(cWhileNode *node)        { VisitAllChildren(node); }
  protected:
    int m_numErrors;
};

