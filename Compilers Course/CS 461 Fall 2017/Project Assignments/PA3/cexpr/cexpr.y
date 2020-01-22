/*
 * This file defines an example yacc grammar for simple C expressions.
 */

%{
#include <stdio.h>
#include <stdlib.h>
int variables[26];
%}

%union {
  int num;
}

%token <num> NUM VAR

%left '+' '-'
%left '*' '/'
%left '='

%type <num> expr

%%

commands:
									commands command
									|
									;

command:
									expr ';'      							{ printf("%d\n", $1); }
									;

expr:	
									| VAR											{ $$ = variables[$1]; }
									| VAR '=' expr 				{ variables[$1] = $3; }
									| expr '+' expr    			{ $$ = $1 + $3; }
									| expr '-' expr    			{ $$ = $1 - $3; }
									| expr '*' expr    			{ $$ = $1 * $3; }
									| expr '/' expr    			{ 
																									if($3==0){
																										yyerror("dividebyzero");
																									}
																									else { $$ = $1 / $3; } 
																								}
									| expr '%' expr    		{ $$ = $1 % $3; }
									| '(' expr ')'							{ $$ = $2; }
									|	NUM                 			{ $$ = $1; }
									;

%%

main()
{
   if (yyparse())
      printf("\nInvalid expression.\n");
   else
      printf("\nCalculator off.\n");
}

yyerror(s)
char *s;
{
   fprintf(stderr, "%s\n", s);
}
