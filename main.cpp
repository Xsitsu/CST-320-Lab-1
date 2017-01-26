//**************************************
// main.cpp
//
// Main routine for lang compiler.
// This version only runs the lexer
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Dec. 15, 2016
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "cSymbol.h"
#include "cSymbolTable.h"
#include "lex.h"
#include "tokens.h"

// Global symbol table definition
// if we had a cSymbolTable.cpp, this definition could go there
cSymbolTable g_SymbolTable;

// If we had a cSymbol.cpp, this definition would go there
long long cSymbol::nextId = 0;

// main routine for compiler
// First command line arg is source file to compile
// Second command line arg is output file
int main(int argc, char **argv)
{
    const char *outfile_name;
    int result = 0;
    int token;

    std::cout << "Philip Howard" << std::endl;

    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL)
        {
            std::cerr << "Unable to open file " << argv[1] << "\n";
            exit(-1);
        }
    }

    if (argc > 2)
        outfile_name = argv[2];
    else
        outfile_name = "/dev/tty";

    std::streambuf *cout_buf = std::cout.rdbuf();
    std::ofstream output(outfile_name);

    if (!output.is_open())
    {
        std::cerr << "Unable to open output file " << outfile_name << "\n";
        exit(-1);
    }
    std::cout.rdbuf(output.rdbuf());

    output << "<program>\n";

    token = yylex();
    while (token != 0)
    {
        // std::cout << token << ":" << yytext << "\n";
        // if we found an identifier, print it out
        if (token == IDENTIFIER) std::cout << yylval.symbol->ToString() << "\n";
        token = yylex();
    }

    output << "</program>\n";

    output.close();
    std::cout.rdbuf(cout_buf);

    return result;
}
