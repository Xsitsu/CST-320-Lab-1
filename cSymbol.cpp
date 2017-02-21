#include "cSymbol.h"

cSymbol::cSymbol(string name, bool is_type) : cAstNode()
{
    m_id = ++nextId;        // get next available ID
    m_name = name;
    m_decl = nullptr;
    m_is_type = is_type;
}

string cSymbol::GetName() { return m_name; }

cDeclNode* cSymbol::GetDecl() { return m_decl; }
void cSymbol::SetDecl(cDeclNode *decl) { m_decl = decl; }

void cSymbol::SetIsType(bool is_type) { this->m_is_type = is_type; }
bool cSymbol::GetIsType() { return this->m_is_type; }

string cSymbol::AttributesToString()
{
    string result(" id=\"");
    result += std::to_string(m_id) + "\"";
    result += " name=\"" + m_name + "\"";
    if (m_decl != nullptr)
    {
        result += " decl=\"" + std::to_string(m_decl->GetName()->m_id);
        result +=  "\"";
    }
    return result;
}

string cSymbol::NodeType() { return string("sym"); }

void cSymbol::Visit(cVisitor *visitor) { visitor->Visit(this); }

