
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

Program:	CLASS ID OBRACE ProgFieldDecl CBRACE	{ }	
		|	CLASS ID OBRACE ProgMethodDecl CBRACE	{ }
		;

ProgFieldDecl:	FieldDecl ProgFieldDecl {}
		|	FieldDecl					{}
		|
		;

ProgMethodDecl:	MethodDecl ProgMethodDecl {}
		|	MethodDecl					 {}
		|
		;

FieldDecl:	STATIC VarDecl	{}
		;

MethodDecl:		PUBLIC STATIC Type ID OCURV FormalParams CCURV OBRACE MethVarDecl MethStatement CBRACE {}
		|		PUBLIC STATIC VOID ID OCURV FormalParams CCURV OBRACE MethVarDecl MethStatement CBRACE {}
		|		PUBLIC STATIC Type ID OCURV CCURV OBRACE MethVarDecl MethStatement CBRACE	{}
		|		PUBLIC STATIC VOID ID OCURV CCURV OBRACE MethVarDecl MethStatement CBRACE	{}
		;

MethVarDecl:	VarDecl MethVarDecl		{}
		|		VarDecl					{}
		|								{}
		;

MethStatement:	Statement MethStatement	{}
		|		Statement				{}
		|								{}
		;

FormalParams:	STRING OSQUARE CSQUARE ID						{}
			|	Type ID CommaTypeID								{}
			;

CommaTypeID:	COMMA Type ID CommaTypeID						{}
			|	COMMA Type ID									{}
			|													{}
			;	

VarDecl:	Type ID CommaID SEMIC								{}
		;

CommaID:	COMMA ID CommaID									{}
		|	COMMA ID											{}
		|														{}
		;

Type:		INT													{}
		|	INT OSQUARE CSQUARE									{}
		|	BOOL												{}
		|	BOOL OSQUARE CSQUARE								{}
		;

Statement: 	OBRACE StatRepeat CBRACE							{}
		|	IF OCURV Expr CCURV	Statement ELSE Statement 		{} 
		|	IF OCURV Expr CCURV Statement						{}
		|	WHILE OCURV Expr CCURV Statement					{}
		|	PRINT OCURV Expr CCURV SEMIC						{}
		|	ID OSQUARE Expr CSQUARE ASSIGN Expr SEMIC			{}
		|	ID ASSIGN Expr SEMIC								{}
		|	RETURN Expr SEMIC									{}
		|	RETURN SEMIC										{}
		;

StatRep:	Statement StatRep				 					{}
		|	Statement											{}
		;

Expr:		Expr OP1 Expr										{}
		|	Expr OP2 Expr										{}
		|	Expr OP3 Expr										{}
		|	Expr OP4 Expr										{}
		|	Expr OSQUARE Expr CSQUARE 							{}
		|	ID													{}
		|	INTLIT												{}
		|	BOOLIT												{}
		|	NEW INT OSQUARE Expr CSQUARE 						{}
		|	NEW BOOL OSQUARE Expr CSQUARE						{}
		|	OCURV Expr CCURV									{}
		|	Expr DOTLENGTH										{}
		|	OP3 Expr											{}
		|	NOT Expr											{}
		|	PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV 		{}
		|	ID OCURV Args CCURV									{}
		|	ID OCURV CCURV										{}
		;

Args:		Expr CommaExpr										{}
		;

CommaExpr:	COMMA Expr CommaExpr								{}
		|	COMMA Expr											{}
		|														{}
		; 


%%

int main()
{
	while(1)
	{
		yyparse();
	}
}



















