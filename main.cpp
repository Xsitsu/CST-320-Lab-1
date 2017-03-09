//**************************************
// main.cpp
//
// Main function for lang compiler
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 28, 2015
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "cSymbolTable.h"
#include "lex.h"
#include "astnodes.h"
#include "langparse.h"
#include "cSizeOffset.h"
#include "cSemantics.h"
#include "cCodeGen.h"
#include "cSymbol.h"

// define global variables
long long cSymbol::nextId;

// takes two string args: input_file, and output_file
int main(int argc, char **argv)
{
    std::cout << "Jacob Locke" << std::endl;

    std::string outfile_name;
    int result = 0;
    //std::streambuf *cout_buf = std::cout.rdbuf();

    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == nullptr)
        {
            std::cerr << "ERROR: Unable to open file " << argv[1] << "\n";
            exit(-1);
        }
    }

    if (argc > 2)
    {
        outfile_name = argv[2];
    } else {
        //outfile_name = "/dev/tty";
        outfile_name = "langout";
    }

    /*
    std::ofstream output(outfile_name);
    if (!output.is_open())
    {
        std::cerr << "ERROR: Unable to open file " << outfile_name << "\n";
        exit(-1);
    }

    // fixup cout so it redirects to output
    std::cout.rdbuf(output.rdbuf());
    */

    g_SymbolTable.InitRootTable();

    result = yyparse();
    if (yyast_root != nullptr)
    {
        cSemantics semantics;
        semantics.VisitAllNodes(yyast_root);
        result += semantics.NumErrors();

        if (result == 0)
        {
            cSizeOffset sizer;
            sizer.VisitAllNodes(yyast_root);

            //std::cout << yyast_root->ToString() << std::endl;

            cCodeGen coder(outfile_name + ".sl");
            coder.VisitAllNodes(yyast_root);

            /*
            string cmd = "gcc -g -O0 -o " + 
                outfile_name + " " + outfile_name + ".c";
            system(cmd.c_str());
            */
        } else {
            std::cerr << yynerrs << " Errors in compile\n";
        }
    }

    if (result == 0 && yylex() != 0)
    {
        std::cerr << "Junk at end of program\n";
    }

    /*
    // close output and fixup cout
    // If these aren't done, you may get a segfault on program exit
    output.close();
    std::cout.rdbuf(cout_buf);
    */

    return result;
}
