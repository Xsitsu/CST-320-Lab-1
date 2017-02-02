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
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
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

%token  PRINT
%token  WHILE IF ELSE ENDIF
%token  STRUCT ARRAY
%token  RETURN
%token  JUNK_TOKEN

 /* NOTE: you will have to change some of these as you complete your lab */
%type <program_node> program
%type <block_node> block
%type <sym_table> open
%type <sym_table> close
%type <decls_node> decls
%type <decl_node> decl
%type <decl_node> var_decl
%type <decl_node> struct_decl
%type <decl_node> array_decl
%type <ast_node> func_decl
%type <ast_node> func_header
%type <symbol> func_prefix
%type <ast_node> func_call
%type <ast_node> paramsspec
%type <ast_node> paramspec
%type <stmts_node> stmts
%type <stmt_node> stmt
%type <ast_node> lval
%type <ast_node> params
%type <ast_node> param
%type <expr_node> expr
%type <expr_node> addit
%type <expr_node> term
%type <expr_node> fact
%type <ast_node> varref
%type <ast_node> varpart

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
                                  $$ = nullptr; // probably want to change this
                                }

close:  '}'                     { g_SymbolTable.DecreaseScope(); 
                                  $$ = nullptr; // probably want to change this
                                }

decls:      decls decl          {}
        |   decl                {}
decl:       var_decl ';'        { $$ = $1; }
        |   struct_decl ';'     {}
        |   array_decl ';'      {}
        |   func_decl           {}
        |   error ';'           {}

var_decl:   TYPE_ID IDENTIFIER  {}
struct_decl:  STRUCT open decls close IDENTIFIER    
                                {}
array_decl: ARRAY TYPE_ID '[' INT_VAL ']' IDENTIFIER
                                {}

func_decl:  func_header ';'
                                {}
        |   func_header  '{' decls stmts '}'
                                {}
        |   func_header  '{' stmts '}'
                                {}
func_header: func_prefix paramsspec ')'
                                {}
        |    func_prefix ')'    {}
func_prefix: TYPE_ID IDENTIFIER '('
                                {}
paramsspec: paramsspec',' paramspec 
                                {}
        |   paramspec           {}

paramspec:  var_decl            {}

stmts:      stmts stmt          {}
        |   stmt                { $$ = new cStmtsNode($1); }

stmt:       IF '(' expr ')' stmts ENDIF ';'
                                {}
        |   IF '(' expr ')' stmts ELSE stmts ENDIF ';'
                                {}
        |   WHILE '(' expr ')' stmt 
                                {}
        |   PRINT '(' expr ')' ';'
                                { $$ = new cPrintNode($3); }
        |   lval '=' expr ';'   {}
        |   lval '=' func_call ';'   {}
        |   func_call ';'       {}
        |   block               {}
        |   RETURN expr ';'     {}
        |   error ';'           {}

func_call:  IDENTIFIER '(' params ')' {}
        |   IDENTIFIER '(' ')'  {}

varref:   varref '.' varpart    {}
        | varref '[' expr ']'   {}
        | varpart               {}

varpart:  IDENTIFIER            { $$ = $1; }

lval:     varref                { $$ = $1; }

params:     params',' param     {}
        |   param               {}

param:      expr                {}

expr:       expr EQUALS addit   {}
        |   addit               { $$ = $1; }

addit:      addit '+' term      {}
        |   addit '-' term      {}
        |   term                { $$ = $1; }

term:       term '*' fact       {}
        |   term '/' fact       {}
        |   term '%' fact       {}
        |   fact                { $$ = $1; }

fact:        '(' expr ')'       {}
        |   INT_VAL             { $$ = new cIntExprNode($1); }
        |   FLOAT_VAL           {}
        |   varref              {}

%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cerr << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}
