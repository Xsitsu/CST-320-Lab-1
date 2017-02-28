#pragma once

class cArrayDeclNode;
class cAssignNode;
class cAstNode;
class cBaseTypeNode;
class cBlockNode;
class cDeclNode;
class cDeclsNode;
class cExprNode;
class cFloatExprNode;
class cFuncCallNode;
class cFuncDeclNode;
class cIfNode;
class cIntExprNode;
class cMathExprNode;
class cOpNode;
class cParamsListNode;
class cParamsNode;
class cPrintNode;
class cProgramNode;
class cReturnNode;
class cStmtNode;
class cStmtsNode;
class cStructDeclNode;
class cSymbol;
class cVarRefNode;
class cWhileNode;

class cVisitor
{
public:
    cVisitor() {}
    
    virtual void VisitAllNodes(cAstNode *node) = 0;
    
    virtual void Visit(cArrayDeclNode* node);
    virtual void Visit(cAssignNode* node);
    virtual void Visit(cAstNode *node);
    virtual void Visit(cBaseTypeNode* node);
    virtual void Visit(cBlockNode *node);
    virtual void Visit(cDeclNode *node);
    virtual void Visit(cDeclsNode *node);
    virtual void Visit(cExprNode *node);
    virtual void Visit(cFloatExprNode* node);
    virtual void Visit(cFuncCallNode* node);
    virtual void Visit(cFuncDeclNode* node);
    virtual void Visit(cIfNode* node);
    virtual void Visit(cIntExprNode *node);
    virtual void Visit(cMathExprNode* node);
    virtual void Visit(cOpNode *node);
    virtual void Visit(cParamsListNode* node);
    virtual void Visit(cParamsNode* node);
    virtual void Visit(cPrintNode *node);
    virtual void Visit(cProgramNode *node);
    virtual void Visit(cReturnNode* node);
    virtual void Visit(cStmtNode *node);
    virtual void Visit(cStmtsNode *node);
    virtual void Visit(cStructDeclNode* node);
    virtual void Visit(cSymbol *node);
    virtual void Visit(cVarRefNode* node);
    virtual void Visit(cWhileNode* node);
    
protected:
    void PreVisitAllNodes(cAstNode *node);
    void PostVisitAllNodes(cAstNode *node);
    void VisitAllChildren(cAstNode *node);
};
