%{
//**************************************
// lang.l
//
// Scanner definition file
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

// Illustration showing how to use {} to control scope

%}

%%

    // control scope with curly braces
    // NOTE: This functionality will eventually move to the parser
"{"                         {
                                IncreaseScope();
                                return yytext[0];
                            }
"}"                         {
                                DecreaseScope();
                                return yytext[0];
                            }
{identifier}                {
                                yylval.symbol = Insert(yytext);
                                return IDENTIFIER;
                            }

%%

