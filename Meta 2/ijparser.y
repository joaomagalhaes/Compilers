
%{
	/* Joao Andre Pedro 2009112620 
	   Joao David Magalhaes 2009112796 */
%}

%{
#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

void yyerror(char* s);
int yylex(void);

is_node *myProgram = NULL;

%}

%union
{
	char* string;
	is_node* node;
}

%token <string> OP1 OP2 OP3 OP4 ID INTLIT BOOLLIT
%token INT BOOL NEW IF ELSE WHILE PRINT PARSEINT CLASS RESERVED
%token PUBLIC STATIC VOID STRING DOTLENGTH RETURN OCURV CCURV
%token OBRACE CBRACE OSQUARE CSQUARE NOT ASSIGN SEMIC COMMA

%type <node> Start Program FieldMethodDecl FieldDecl MethodDecl
%type <node> MethVarDecl FormalParams CommaTypeID VarDecl CommaID Type
%type <node> Statement StatRep Expr Args CommaExpr

%left DOTLENGTH
%right ASSIGN
%left OP1
%left OP2
%left OP3
%left OP4
%right NOT
%left OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE

%nonassoc ELSE

%%

Start:	Program 	{ $$=insertStart($1); myProgram=$$; }
		;

Program:	CLASS ID OBRACE FieldMethodDecl CBRACE { $$=insertProgram($4); }	
			;

FieldMethodDecl:	FieldDecl FieldMethodDecl {}
				|	MethodDecl FieldMethodDecl {}
				|							{}
				;

FieldDecl:	STATIC VarDecl	{}
		;

MethodDecl:		PUBLIC STATIC Type ID OCURV FormalParams CCURV OBRACE MethVarDecl StatRep CBRACE {}
		|		PUBLIC STATIC VOID ID OCURV FormalParams CCURV OBRACE MethVarDecl StatRep CBRACE {}
		|		PUBLIC STATIC Type ID OCURV CCURV OBRACE MethVarDecl StatRep CBRACE	{}
		|		PUBLIC STATIC VOID ID OCURV CCURV OBRACE MethVarDecl StatRep CBRACE	{}
		;

MethVarDecl:	VarDecl MethVarDecl		{}
		|								{}
		;

FormalParams:	STRING OSQUARE CSQUARE ID						{}
			|	Type ID CommaTypeID								{}
			;

CommaTypeID:	COMMA Type ID CommaTypeID						{}
			|													{}
			;	

VarDecl:	Type ID CommaID SEMIC								{}
		;

CommaID:	COMMA ID CommaID									{}
		|														{}
		;

Type:		INT													{}
		|	INT OSQUARE CSQUARE									{}
		|	BOOL												{}
		|	BOOL OSQUARE CSQUARE								{}
		;

Statement: 	OBRACE StatRep CBRACE								{}
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
		|														{}
		;

Expr:		Expr OP1 Expr										{}
		|	Expr OP2 Expr										{}
		|	Expr OP3 Expr										{}
		|	Expr OP4 Expr										{}
		|	Expr OSQUARE Expr CSQUARE 							{}
		|	ID													{}
		|	INTLIT												{}
		|	BOOLLIT												{}
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
		|														{}
		; 


%%

int main(int argc, char **argv)
{
	if( yyparse() == 0)
		printf("bom parsing modafocka\n");
}

void yyerror(char* s)
{
	printf("deu merda boiii");
	exit(0);
}

