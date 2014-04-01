
%{
	/* Joao Andre Pedro 2009112620 
	   Joao David Magalhaes 2009112796 */
%}

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char* s);

%}

%union
{
	char* string;
}

%token BOOLLIT INT BOOL NEW IF ELSE WHILE PRINT
%token 
