
%{
	/* Joao Andre Pedro 2009112620 
	   Joao David Magalhaes 2009112796 */
%}

%{
#include "structures.h"
#include "functions.h"
#include "shows.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

void yyerror(char* s);
int yylex(void);

int line, col, yyleng;
char *yytext;

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

Start:	Program		{ printf("Start\n");}
		;

Program:	CLASS ID OBRACE FieldMethodDecl CBRACE { $$ = insertProgram(insert_ID($2), $4); myProgram=$$; printf("Criacao de classe\n"); }	
			;

FieldMethodDecl:	FieldDecl FieldMethodDecl 	{ $$ = insertRepetition($1, $2); }
				|	MethodDecl FieldMethodDecl 	{ $$ = insertRepetition($1, $2); }
				|								{ $$ = NULL; }
				;

FieldDecl:	STATIC VarDecl	{ $$ = $2; }
		;

MethodDecl:		PUBLIC STATIC Type ID OCURV FormalParams CCURV OBRACE MethVarDecl StatRep CBRACE 	{ $$ = insertMethodDecl($3, insert_ID($4), $6, $9, $10); printf("Declaracao de Metodo\n"); }
		|		PUBLIC STATIC VOID ID OCURV FormalParams CCURV OBRACE MethVarDecl StatRep CBRACE 	{ $$ = insertMethodDecl(insertType(Void), insert_ID($4), $6, $9, $10); printf("Declaracao de Metodo\n"); } 
		|		PUBLIC STATIC Type ID OCURV CCURV OBRACE MethVarDecl StatRep CBRACE					{ $$ = insertMethodDecl($3, insert_ID($4), NULL, $8, $9); printf("Declaracao de Metodo\n"); }
		|		PUBLIC STATIC VOID ID OCURV CCURV OBRACE MethVarDecl StatRep CBRACE					{ $$ = insertMethodDecl(insertType(Void), insert_ID($4), NULL, $8, $9); printf("Declaracao de Metodo\n"); }
		;

MethVarDecl:	VarDecl MethVarDecl		{ $$ = insertRepetition($1, $2); }
		|								{ $$ = NULL; printf("MethVarDecl - NULL\n"); }
		;

FormalParams:	STRING OSQUARE CSQUARE ID		{ $$ = insertFormalParams1(insertType(StringArray), insert_ID($4)); }
			|	Type ID CommaTypeID				{ $$ = insertFormalParams2($1, insert_ID($2), $3); }
			;

CommaTypeID:	COMMA Type ID CommaTypeID		{ $$ = insertFPRepetition($2, insert_ID($3)); }
			|									{ $$ = NULL; printf("CommaTypeID - NULL\n"); }
			;	

VarDecl:	Type ID CommaID SEMIC		{ $$ = insertVarDecl($1, insert_ID($2), $3); printf("VarDecl\n"); }
		;

CommaID:	COMMA ID CommaID			{ $$ = insertRepetition(insert_ID($2), $3); }
		|								{ $$ = NULL; printf("CommaID - NULL\n"); }
		;

Type:		INT							{ $$ = insertType(Int); }
		|	INT OSQUARE CSQUARE			{ $$ = insertType(IntArray); }
		|	BOOL						{ $$ = insertType(Bool); }
		|	BOOL OSQUARE CSQUARE		{ $$ = insertType(BoolArray); }
		;

Statement: 	OBRACE StatRep CBRACE								{ $$ = $2; }
		|	IF OCURV Expr CCURV	Statement ELSE Statement 		{ $$ = insertST_if_else($3, $5, $7); } 
		|	IF OCURV Expr CCURV Statement						{ $$ = insertST_if_else($3, $5, NULL); }
		|	WHILE OCURV Expr CCURV Statement					{}
		|	PRINT OCURV Expr CCURV SEMIC						{}
		|	ID OSQUARE Expr CSQUARE ASSIGN Expr SEMIC			{}
		|	ID ASSIGN Expr SEMIC								{}
		|	RETURN Expr SEMIC									{ $$ = insertST_ret_exp_sem($2); }
		|	RETURN SEMIC										{}
		;

StatRep:	Statement StatRep		{ $$ = insertRepetition($1, $2); }
		|							{ $$ = NULL; printf("StatRep - NULL\n"); }
		;

Expr:		Expr OP1 Expr										{}
		|	Expr OP2 Expr										{}
		|	Expr OP3 Expr										{}
		|	Expr OP4 Expr										{}
		|	Expr OSQUARE Expr CSQUARE 							{}
		|	ID													{ $$ = insert_ID($1); printf("Expr ID\n"); }
		|	INTLIT												{ $$ = insert_INTLIT($1); printf("Expr INTLIT\n"); }
		|	BOOLLIT												{ /* $$ = insert_BOOLLIT($1); printf("Expr BOOLLIT\n"); */}
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
		|														{ $$ = NULL; printf("CommaExpr - NULL\n"); }
		; 


%%

int main(int argc, char **argv)
{
	line = 1;
	col = 1;

	if(yyparse() == 0)
	{
		printf("\nParsing sucessfull - Printing AST\n\n");
		if(myProgram != NULL)
			printAST(myProgram, 0);
	}
}

void yyerror(char* s)
{
	printf("Line %d, col %d: %s: %s\n", line, col - yyleng, s, yytext);
	exit(0);
}

