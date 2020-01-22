%{
#include<stdlib.h>
#include "y.tab.h"
%}
%%

[0-9]+    						{ sscanf(yytext, "%d", &yylval); //Returns Integers
														return NUM; }
[a-z]*									{ sscanf(yytext, "%c", &yylval); //Returns Variable
														return VAR;
													}
[()~&^|<>=]*		{ sscanf(yytext, "%c", &yylval); //Returns Operators
														return *yytext; }
[ \t]										;

.           							{ return yytext[0]; }
%%