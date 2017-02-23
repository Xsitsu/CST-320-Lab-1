#pragma once

#include <iostream>

#include "cAstNode.h"
#include "cDeclNode.h"

#include "cParamsNode.h"
#include "cDeclsNode.h"
#include "cStmtsNode.h"

class cFuncDeclNode : public cDeclNode
{
private:
cFuncDeclNode(cSymbol* type, cSymbol* id) : cDeclNode(),
        params(NULL), decls(NULL), stmts(NULL)
    {
        this->AddChild(type);
        this->AddChild(id);
    
        id->SetDecl(this);
    }

public:
    static cFuncDeclNode* Make(cSymbol* type, cSymbol* id)
    {
        if (!g_SymbolTable.FindLocal(id->GetName()))
        {
            if(g_SymbolTable.Find(id->GetName()))
            {
                id = new cSymbol(id->GetName());
            }
            
            g_SymbolTable.Insert(id);
        }
        
        cDeclNode* old = g_SymbolTable.Find(id->GetName())->GetDecl();
        if (old)
        {
            if (!old->IsFunc())
            {
                string err;
                err += id->GetName();
                err += " previously declared as other than a function";
                SemanticError(err);
            }
            else if (old->GetType() != type->GetDecl())
            {
                string err;
                err += id->GetName();
                err += " previously declared with different return type";
                SemanticError(err);
            }
            else
            {
                cFuncDeclNode* decl = new cFuncDeclNode(type, id);
                cFuncDeclNode* decl_old = static_cast<cFuncDeclNode*>(old);
                
                decl->params = decl_old->GetParams();
                decl->decls = decl_old->GetDecls();
                decl->stmts = decl_old->GetStmts();
                
                return decl;
            }
        }
        
        return new cFuncDeclNode(type, id);
    }
    
    virtual string NodeType() { return string("func"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    virtual cSymbol* GetName()
    {
        return static_cast<cSymbol*>(this->GetChild(1));
    }

    virtual cDeclNode* GetType()
    {
        return static_cast<cSymbol*>(this->GetChild(0))->GetDecl();
    }
    
    virtual bool IsFunc() { return true; }
    
    cParamsNode* params;
    cDeclsNode* decls;
    cStmtsNode* stmts;
    
    void AddParams(cParamsNode* params)
    {
        if (this->params)
        {
            int num_children = this->params->NumChildren();
            if (num_children != params->NumChildren())
            {
                string err;
                err += this->GetName()->GetName();
                err += " previously declared with a different number of parameters";
                SemanticError(err);
            }
            
            for (int i = 0; i < num_children; i++)
            {
                cVarDeclNode* old = this->params->GetParam(i);
                cVarDeclNode* add = params->GetParam(i);
                
                if (old->GetType() != add->GetType())
                {
                    string err;
                    err += this->GetName()->GetName();
                    err += " previously declared with different parameters";
                    SemanticError(err);
                }
            }
        }
        
        
        this->params = params;
        this->AddChild(params);
    }
    
    void AddDefinition(cDeclsNode* decls, cStmtsNode* stmts)
    {
        if (this->stmts)
        {
            string err;
            err += this->GetName()->GetName();
            err += " already has a definition";
            SemanticError(err);
        }
        
        if (decls)
        {
            this->decls = decls;
            this->AddChild(decls);
        }

        this->stmts = stmts;
        this->AddChild(stmts);
    }
    
    cParamsNode* GetParams()
    {
        return this->params;
    }
    
    cDeclsNode* GetDecls()
    {
        return this->decls;
    }
    
    cStmtsNode* GetStmts()
    {
        return this->stmts;
    }
};
