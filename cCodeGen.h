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
    
    
    
    void Visit(cBinaryExprNode* node)
    {
        node->GetLeft()->Visit(this);
        node->GetRight()->Visit(this);
        node->GetOp()->Visit(this);
    }
    
    void Visit(cIntExprNode* node)
    {
        std::cout << "PUSH " << node->GetValue() << std::endl;
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
        
        std::cout << opname << std::endl;
    }
    
    void Visit(cVarExprNode* node)
    {
        std::cout << "PUSHVAR " << node->GetOffset() << std::endl;
    }
    
    void Visit(cAssignNode* node)
    {
        node->GetExpr()->Visit(this);
        std::cout << "POPVAR " << node->GetLVal()->GetOffset() << std::endl;
    }
    
    
    
protected:
    
};
