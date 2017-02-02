#pragma once

class cAstNode;
class cBlockNode;
class cDeclNode;
class cDeclsNode;
class cExprNode;
class cIntExprNode;
class cOpNode;
class cPrintNode;
class cProgramNode;
class cStmtNode;
class cStmtsNode;
class cSymbol;

class cVisitor
{
    public:
        cVisitor() {}

        virtual void VisitAllNodes(cAstNode *node) = 0;

        virtual void Visit(cAstNode *node);
        virtual void Visit(cBlockNode *node);
        virtual void Visit(cDeclNode *node);
        virtual void Visit(cDeclsNode *node);
        virtual void Visit(cExprNode *node);
        virtual void Visit(cIntExprNode *node);
        virtual void Visit(cOpNode *node);
        virtual void Visit(cPrintNode *node);
        virtual void Visit(cProgramNode *node);
        virtual void Visit(cStmtNode *node);
        virtual void Visit(cStmtsNode *node);
        virtual void Visit(cSymbol *node);
    protected:
        void PreVisitAllNodes(cAstNode *node);
        void PostVisitAllNodes(cAstNode *node);
        void VisitAllChildren(cAstNode *node);
};
