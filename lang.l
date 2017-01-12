%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include "tokens.h"

#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
period          ['.']

%%

    // token definitions go here. "if" is an example.
"array"                     DO_RETURN(ARRAY);
"if"                        DO_RETURN(IF);
"else"                      DO_RETURN(ELSE);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       DO_RETURN(INT);
"float"                     DO_RETURN(FLOAT);
"char"                      DO_RETURN(CHAR);
"struct"                    DO_RETURN(STRUCT);
"return"                    DO_RETURN(RETURN);


%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

