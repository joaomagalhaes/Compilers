
%{
	/* Joao Andre Pedro 2009112620 
	   Joao David Magalhaes 2009112796 */
%}

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char* s);
int yylex(void);

%}

%union
{
	char* string;
}

%token <string> BOOLLIT
%token <string> OP1
%token <string> OP2
%token <string> OP3
%token <string> OP4
%token <string> ID
%token <string> INTLIT
%token INT BOOL NEW IF ELSE WHILE PRINT PARSEINT CLASS RESERVED
%token PUBLIC STATIC VOID STRING DOTLENGTH RETURN OCURV CCURV
%token OBRACE CBRACE OSQUARE CSQUARE NOT ASSIGN SEMIC COMMA

%%

Start:		Program 	{ myProgram==$$; }

Program:	CLASS ID OBRACE FieldDecl CBRACE	{ $$=insertProgram($4); }	
		|	CLASS ID OBRACE MethodDecl CBRACE	{ $$=insertProgram($4); }
		;

FieldDecl:	STATIC VarDecl	{ $$=insertFieldDecl($2); }
		;

MethodDecl:	PUBLIC STATIC Type ID OCURV {}
		|	PUBLIC STATIC VOID ID OCURV {}
		|	PUBLIC STATIC ID OCURV {}
		;



Statement: 	OBRACE Statement CBRACE		{}
		|	IF OCURV Expr CCURV 



Expr:	Expr OP1 Expr					{ $$=insertExpr_Oper_Expr($1, OP1, $3); }
	|	Expr OP2 Expr					{ $$=insertExpr_Oper_Expr($1, OP2, $3); }
	|	Expr OP3 Expr					{ $$=insertExpr_Oper_Expr($1, OP3, $3); }
	|	Expr OP4 Expr	
	|	Expr OSQUARE Expr CSQUARE 		{}
	|	ID								{}
	|	INTLIT							{}
	|	BOOLIT							{}
	|	NEW INT OSQUARE Expr CSQUARE 	{}
	|	NEW BOOL OSQUARE Expr CSQUARE	{}
	|	OCURV Expr CCURV				{}
	|	Expr DOTLENGTH					{}
	|	OP3 Expr						{}
	|	NOT Expr						{}
	|	PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV {}
	|	ID OCURV Args CCURV				{}
	|	Expr CommaExp					{}

CommaExp:	

Args: 


%%

int main()
{
	while(1)
	{
		yyparse();
	}
}



















