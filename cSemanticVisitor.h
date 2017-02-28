#pragma once

#include <string>

#include "cVisitor.h"
#include "cAstNode.h"

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
    
};
