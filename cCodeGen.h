#pragma once

#include <string>

#include "cVisitor.h"
#include "emit.h"

class cCodeGen : public cVisitor
{
public:
    cCodeGen(const std::string output_file)
    {
        InitOutput(output_file);
    }
    
    ~cCodeGen()
    {
        FinalizeOutput();
    }
    
    void VisitAllNodes(cAstNode* node)
    {
        node->Visit(this);
    }
    
    
    void Visit(cBlockNode* node)
    {
        EmitString("ADJSP");
        EmitInt(node->GetSize());
        EmitString("\n");
        
        this->VisitAllChildren(node);
        
        EmitString("ADJSP");
        EmitInt(-node->GetSize());
        EmitString("\n");
    }
    
    void Visit(cBinaryExprNode* node)
    {
        node->GetLeft()->Visit(this);
        node->GetRight()->Visit(this);
        node->GetOp()->Visit(this);
    }
    
    void Visit(cIntExprNode* node)
    {
        EmitString("PUSH");
        EmitInt(node->GetValue());
        EmitString("\n");
    }
    
    void Visit(cOpNode* node)
    {
        std::string opname = "";
        
        switch (node->GetOp())
        {
        case '+':
            opname = "PLUS";
            break;
        case '-':
            opname = "MINUS";
            break;
        case '*':
            opname = "TIMES";
            break;
        case '/':
        case '%':
            opname = "DIVIDE";
            break;
        }
        
        EmitString(opname);
        EmitString("\n");
    }
    
    void Visit(cVarExprNode* node)
    {
        EmitString("PUSHVAR");
        EmitInt(node->GetOffset());
        EmitString("\n");
    }
    
    void Visit(cAssignNode* node)
    {
        node->GetExpr()->Visit(this);
        
        EmitString("POPVAR");
        EmitInt(node->GetLVal()->GetOffset());
        EmitString("\n");
    }
    
    void Visit(cPrintNode* node)
    {
        this->VisitAllChildren(node);
        
        EmitString("CALL @print\n");
    }
    
    void Visit(cFuncDeclNode* node)
    {
        StartFunctionOutput(node->GetName()->GetName());
        
        int adjust = node->GetSize();
        
        EmitString("ADJSP");
        EmitInt(adjust);
        EmitString("\n");
        
        this->VisitAllChildren(node);
        
        EmitString("ADJSP");
        EmitInt(-adjust);
        EmitString("\n");
        
        EmitString("RETURNV\n");
        
        EndFunctionOutput();
    }
    
    void Visit(cFuncExprNode* node)
    {
        EmitString("CALL @");
        EmitString(node->GetName()->GetName());
        EmitString("\n");
    }
    
    void Visit(cReturnNode* node)
    {
        this->VisitAllChildren(node);
    }
    
protected:
    
};
