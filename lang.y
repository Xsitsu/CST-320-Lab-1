%{
//**************************************
// lang.y
//
// Parser definition file. bison uses this file to generate the parser.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Dec. 18, 2016
//
#include <iostream>
#include "lex.h"
#include "astnodes.h"

%}

%locations

 /* union defines the type for lexical values */
%union{
    int             int_val;
    double          float_val;
    cAstNode*       ast_node;
    cProgramNode*   program_node;
    cBlockNode*     block_node;
    cStmtsNode*     stmts_node;
    cStmtNode*      stmt_node;
    cExprNode*      expr_node;
    cSymbol*        symbol;
    cSymbolTable::symbolTable_t*  sym_table;
    cDeclNode*      decl_node;
    cDeclsNode*     decls_node;
    
    cAstNode*       paramsspec_node;
    cAstNode*       paramspec_node;
    cParamsListNode*params_node;
    cVarRefNode*    varref_node;
    cAstNode*       varpart_node;
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
    
    void SemanticError(std::string error);
%}

%start  program

%token <symbol>    IDENTIFIER
%token <symbol>    TYPE_ID
%token <int_val>   CHAR_VAL
%token <int_val>   INT_VAL
%token <float_val> FLOAT_VAL
%token <int_val>   AND
%token <int_val>   OR
%token <int_val>   EQUALS
%token <int_val>   MULT
%token <int_val>   DIV
%token <int_val>   ADD
%token <int_val>   SUB
%token <int_val>   MOD

%token  PRINT
%token  WHILE IF ELSE ENDIF
%token  STRUCT ARRAY
%token  RETURN
%token  JUNK_TOKEN


%type <program_node> program
%type <block_node> block
%type <sym_table> open
%type <sym_table> close
%type <decls_node> decls
%type <decl_node> decl
%type <decl_node> var_decl
%type <decl_node> struct_decl
%type <decl_node> array_decl
%type <decl_node> func_decl
%type <decl_node> func_header
%type <decl_node> func_prefix
%type <expr_node> func_call
%type <paramsspec_node> paramsspec
%type <decl_node> paramspec
%type <stmts_node> stmts
%type <stmt_node> stmt
%type <varref_node> lval
%type <params_node> params
%type <expr_node> param
%type <expr_node> expr
%type <expr_node> addit
%type <expr_node> term
%type <expr_node> fact
%type <varref_node> varref
%type <symbol> varpart

%%

program: block                  { $$ = new cProgramNode($1);
                                  yyast_root = $$;
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
block:  open decls stmts close  { $$ = new cBlockNode($2, $3); }
    |   open stmts close        { $$ = new cBlockNode(nullptr, $2); }

open:   '{'                     { g_SymbolTable.IncreaseScope(); 
                                }

close:  '}'                     { g_SymbolTable.DecreaseScope(); 
                                }

decls:      decls decl          { $$->AddChild($2); }
        |   decl                { $$ = new cDeclsNode($1); }
decl:       var_decl ';'        { $$ = $1; }
        |   struct_decl ';'     { $$ = $1; }
        |   array_decl ';'      { $$ = $1; }
        |   func_decl           { $$ = $1; g_SymbolTable.DecreaseScope(); }
        |   error ';'           { }

var_decl:   TYPE_ID IDENTIFIER  {
                                    //if (g_SymbolTable.Find($2->GetName()))
                                    //{
                                        //$2 = new cSymbol($2->GetName());
                                    //}
                                    //g_SymbolTable.Insert($2);
                                    $$ = new cVarDeclNode($1, $2);
                                }

struct_decl:  STRUCT open decls close IDENTIFIER    
                                {
                                    if (g_SymbolTable.Find($5->GetName()))
                                    {
                                        $5 = new cSymbol($5->GetName());
                                    }
                                    g_SymbolTable.Insert($5);
                                    $$ = new cStructDeclNode($3, $5);
                                }

array_decl: ARRAY TYPE_ID '[' INT_VAL ']' IDENTIFIER
                                {
                                    if (g_SymbolTable.Find($6->GetName()))
                                    {
                                        $6 = new cSymbol($6->GetName());
                                    }
                                    g_SymbolTable.Insert($6);
                                    $$ = new cArrayDeclNode($4, $2, $6);
                                }

func_decl:  func_header ';'
                                {
                                    $$ = $1;
                                }
        |   func_header  '{' decls stmts '}'
                                {
                                    $$ = $1;
                                    $$->AddChild($3);
                                    $$->AddChild($4);
                                }
        |   func_header  '{' stmts '}'
                                {
                                    $$ = $1;
                                    $$->AddChild($3);
                                }
func_header: func_prefix paramsspec ')'
                                {
                                    $$ = $1;
                                    $$->AddChild($2);
                                }
        |    func_prefix ')'    {
                                    $$ = $1; 
                                }

func_prefix: TYPE_ID IDENTIFIER '('
                                {
                                    //if (g_SymbolTable.Find($2->GetName()))
                                    //{
                                        //$2 = new cSymbol($2->GetName());
                                    //}
                                    //g_SymbolTable.Insert($2);

                                    $$ = cFuncDeclNode::Make($1, $2);
                                    
                                    g_SymbolTable.IncreaseScope();
                                }
paramsspec: paramsspec',' paramspec 
                                { $$ = $1; $$->AddChild($3); }
        |   paramspec           { $$ = new cParamsNode($1); }

paramspec:  var_decl            { $$ = $1; }

stmts:      stmts stmt          { $$ = $1; $$->Insert($2); }
        |   stmt                { $$ = new cStmtsNode($1); }

stmt:       IF '(' expr ')' stmts ENDIF ';'
                                { $$ = new cIfNode($3, $5); }
        |   IF '(' expr ')' stmts ELSE stmts ENDIF ';'
                                { $$ = new cIfNode($3, $5, $7); }
        |   WHILE '(' expr ')' stmt 
                                { $$ = new cWhileNode($3, $5);  }
        |   PRINT '(' expr ')' ';'
                                { $$ = new cPrintNode($3); }
        |   lval '=' expr ';'   { $$ = new cAssignNode($1, $3); }
        |   lval '=' func_call ';'   { $$ = new cAssignNode($1, $3); }
        |   func_call ';'       { $$ = $1; }
        |   block               { $$ = $1; }
        |   RETURN expr ';'     { $$ = new cReturnNode($2); }
        |   error ';'           {}

func_call:  IDENTIFIER '(' params ')' { $$ = new cFuncCallNode($1, $3); }
        |   IDENTIFIER '(' ')'  { $$ = new cFuncCallNode($1); }

varref:   varref '.' varpart    { $$ = $1; $$->AddChild($3); }
        | varref '[' expr ']'   { $$ = $1; $$->AddChild($3); }
        | varpart               { $$ = new cVarRefNode($1); }

varpart:  IDENTIFIER            { $$ = $1; }

lval:     varref                { $$ = $1; }

params:     params',' param     { $$ = $1; $$->AddChild($3); }
        |   param               { $$ = new cParamsListNode($1); }

param:      expr                { $$ = $1; }

expr:       expr EQUALS addit   { $$ = new cMathExprNode($$, new cOpNode(EQUALS), $3); }
        |   addit               { $$ = $1; }

addit:      addit '+' term      { $$ = new cMathExprNode($$, new cOpNode(ADD), $3); }
        |   addit '-' term      { $$ = new cMathExprNode($$, new cOpNode(SUB), $3); }
        |   term                { $$ = $1; }
term:       term '*' fact       { $$ = new cMathExprNode($$, new cOpNode(MULT), $3); }
        |   term '/' fact       { $$ = new cMathExprNode($$, new cOpNode(DIV), $3); }
        |   term '%' fact       { $$ = new cMathExprNode($$, new cOpNode(MOD), $3); }
        |   fact                { $$ = $1; }

fact:        '(' expr ')'       { $$ = $2; }
        |   INT_VAL             { $$ = new cIntExprNode($1); }
        |   FLOAT_VAL           { $$ = new cFloatExprNode($1); }
        |   varref              { $$ = $1; }

%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cerr << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}

// Function that gets called when a semantic error happens
void SemanticError(std::string error)
{
    std::cout << "ERROR: " << error << " on line " 
              << yylineno << "\n";
    yynerrs++;
}
