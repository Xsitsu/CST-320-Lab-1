//*******************************************************
// Purpose: Utility routines used for code generation
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
//
// Date: 2/25/2016
//
//*******************************************************

#include <iostream>
#include <stdio.h>
#include <string>
#include "emit.h"

using std::string;

void RewriteFunctions();

// Output files
static FILE* Output;
static FILE* Functions;
static FILE* Active;

static int  Next_Label = 1;

#define PRELUDE \
    ".function main\n" \
    "main:\n"

#define POSTLUDE \
    "PUSH 0\n" \
    "RETURNV\n"

//*****************************************
// Open output files and write the prefix
bool InitOutput(const std::string filename)
{
    Output = fopen(filename.c_str(), "w");
    if (Output == NULL)
    {
        std::cerr << "Unable to open output file." << std::endl;
        return false;
    }

    Functions = tmpfile();
    if (Functions == NULL)
    {
        std::cerr << "Unable to open functions output file." << std::endl;
        return false;
    }

    Active = Output;

    fprintf(Active, "%s", PRELUDE);

    return true;
}
//*****************************************
// output postfix, copy functions to tail of main file and close files
bool FinalizeOutput()
{
    fprintf(Active, "%s", POSTLUDE);

    RewriteFunctions();

    fclose(Output);
    fclose(Functions);

    return true;
}
//*****************************************
// Generate a unique label for GOTO statements
std::string GenerateLabel()
{
    Next_Label++;
    std::string label("$LANG_LABEL");
    label += std::to_string(Next_Label);
    return label;
}
//*****************************************
void StartFunctionOutput(string func_name)
{
    Active = Functions;
    fprintf(Active, ".function %s\n%s:\n", func_name.c_str(),func_name.c_str());
}
//*****************************************
void EndFunctionOutput()
{
    fprintf(Active, "PUSH 0\nRETURNV\n");
    Active = Output;
}
//*****************************************
void RewriteFunctions()
{
    char buff[1000];

    rewind(Functions);

    while (fgets(buff, sizeof(buff), Functions) != NULL)
    {
        fputs(buff, Output);
    }
}



//*****************************************
// write an integer constant to the output
void EmitInt(int val)
{
    fprintf(Active, " %d ", val);
}
//*****************************************
void EmitString(std::string str)
{
    fprintf(Active, "%s", str.c_str());
}
