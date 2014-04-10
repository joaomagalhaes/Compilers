
%{
	/* Joao Andre Pedro 2009112620 
	   Joao David Magalhaes 2009112796 */
%}

%{
#include "structures.h"
#include "functions.h"
#include "shows.h"
//#include "semantics.h"
//#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

void yyerror(char* s);
int yylex(void);

int line, col, yyleng;
char *yytext;

is_node *myProgram = NULL;
//prog_env *mySemantic = NULL;

%}

%union
{
	char* string;
	is_node* node;
}

%token <string> OP1 OP15 OP2 OP25 OP3 OP4 ID INTLIT BOOLLIT
%token INT BOOL NEW IF ELSE WHILE PRINT PARSEINT CLASS RESERVED
%token PUBLIC STATIC VOID STRING DOTLENGTH RETURN OCURV CCURV
%token OBRACE CBRACE OSQUARE CSQUARE NOT ASSIGN SEMIC COMMA

%type <node> Start Program FieldMethodDecl FieldDecl MethodDecl
%type <node> MethVarDecl FormalParams CommaTypeID VarDecl CommaID Type
%type <node> Statement StatRep Expr Args CommaExpr

%right ASSIGN
%left OP1
%left OP15
%left OP2
%left OP25
%left OP3
%left OP4
%right NEW
%right NOT
%left OCURV CCURV OSQUARE CSQUARE
%left DOTLENGTH

%nonassoc ELSE

%%

Start:	Program		{ $$ = insertProgram($1); myProgram = $$; }
		;

Program:	CLASS ID OBRACE FieldMethodDecl CBRACE { $$ = insertProgAux(insert_ID($2), $4); }	
			;

FieldMethodDecl:	FieldDecl FieldMethodDecl	{ $$ = insertRepetition($1, $2); }
				|	MethodDecl FieldMethodDecl 	{ $$ = insertRepetition($1, $2); }
				|								{ $$ = NULL; }
				;

FieldDecl:	STATIC VarDecl	{ $$ = $2; }
		;

MethodDecl:		PUBLIC STATIC Type ID OCURV FormalParams CCURV OBRACE MethVarDecl StatRep CBRACE 	{ $$ = insertMethodDecl($3, insert_ID($4), $6, $9, $10); }
		|		PUBLIC STATIC VOID ID OCURV FormalParams CCURV OBRACE MethVarDecl StatRep CBRACE 	{ $$ = insertMethodDecl(insertType(Void), insert_ID($4), $6, $9, $10); } 
		|		PUBLIC STATIC Type ID OCURV CCURV OBRACE MethVarDecl StatRep CBRACE					{ $$ = insertMethodDecl($3, insert_ID($4), NULL, $8, $9); }
		|		PUBLIC STATIC VOID ID OCURV CCURV OBRACE MethVarDecl StatRep CBRACE					{ $$ = insertMethodDecl(insertType(Void), insert_ID($4), NULL, $8, $9); }
		;

MethVarDecl:	VarDecl MethVarDecl		{ $$ = insertRepetition($1, $2); }
		|								{ $$ = NULL; }
		;

FormalParams:	STRING OSQUARE CSQUARE ID		{ $$ = insertFormalParams1(insertType(StringArray), insert_ID($4)); }
			|	Type ID CommaTypeID				{ $$ = insertFormalParams2($1, insert_ID($2), $3); }
			;

CommaTypeID:	COMMA Type ID CommaTypeID		{ $$ = insertFPRepetition($2, insert_ID($3)); }
			|									{ $$ = NULL; }
			;	

VarDecl:	Type ID CommaID SEMIC		{ $$ = insertVarDecl($1, insert_ID($2), $3); }
		;

CommaID:	COMMA ID CommaID			{ $$ = insertRepetition(insert_ID($2), $3); }
		|								{ $$ = NULL; }
		;

Type:		INT							{ $$ = insertType(Int); }
		|	INT OSQUARE CSQUARE			{ $$ = insertType(IntArray); }
		|	BOOL						{ $$ = insertType(Bool); }
		|	BOOL OSQUARE CSQUARE		{ $$ = insertType(BoolArray); }
		;

Statement: 	OBRACE StatRep CBRACE								{ $$ = insertST_compoundstat($2); }
		|	IF OCURV Expr CCURV	Statement ELSE Statement 		{ $$ = insertST_if_else($3, $5, $7); } 
		|	IF OCURV Expr CCURV Statement						{ $$ = insertST_if_else($3, $5, NULL); }
		|	WHILE OCURV Expr CCURV Statement					{ $$ = insertST_while_expr_stat($3, $5); }
		|	PRINT OCURV Expr CCURV SEMIC						{ $$ = insertST_print_expr_sem($3); }
		|	ID OSQUARE Expr CSQUARE ASSIGN Expr SEMIC			{ $$ = insertST_id_expr_assign_expr(insert_ID($1), $3, $6); }
		|	ID ASSIGN Expr SEMIC								{ $$ = insertST_id_assign_exp_sem(insert_ID($1), $3); }
		|	RETURN Expr SEMIC									{ $$ = insertST_ret_exp_sem($2); }
		|	RETURN SEMIC										{ $$ = nullNode(); }
		;

StatRep:	Statement StatRep		{ $$ = insertRepetition($1, $2); }
		|							{ $$ = NULL;  }
		;

Expr:		Expr OP1 Expr										{ $$ = insert_expr_ope_expr($1, $2, $3); }
		| 	Expr OP15 Expr 										{ $$ = insert_expr_ope_expr($1, $2, $3); }
		|	Expr OP2 Expr										{ $$ = insert_expr_ope_expr($1, $2, $3); }
		|	Expr OP25 Expr 										{ $$ = insert_expr_ope_expr($1, $2, $3); }
		|	Expr OP3 Expr										{ $$ = insert_expr_ope_expr($1, $2, $3); }
		|	Expr OP4 Expr										{ $$ = insert_expr_ope_expr($1, $2, $3); }
		|	ID													{ $$ = insert_ID($1); }
		|	INTLIT												{ $$ = insert_INTLIT($1); }
		|	BOOLLIT												{ $$ = insert_BOOLLIT($1); }
		|	OCURV Expr CCURV									{ $$ = $2; /*review*/ }
		|	Expr DOTLENGTH										{ $$ = insert_length($1); }
		|	OP3 Expr											{ $$ = insert_Oper_Exp($1, $2); }
		|	NOT Expr											{ $$ = insert_Oper_Exp("!", $2); } 
		|	PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV 		{ $$ = insert_ParseInt(insert_ID($3), $5); }
		|	ID OCURV Args CCURV									{ $$ = insert_id_args(insert_ID($1), $3); }  
		|	ID OCURV CCURV										{ $$ = insert_ID($1); }
		|	Expr OSQUARE Expr CSQUARE  	                        { $$ = insert_expr_squares_expr($1, $3); }
		|	NEW INT OSQUARE Expr CSQUARE                        { $$ = insert_new_exp(NewInt, $4); }
		|   NEW BOOL OSQUARE Expr CSQUARE                       { $$ = insert_new_exp(NewBool, $4); }
		;

Args:		Expr CommaExpr				{ $$ = insertRepetition($1, $2); }
		;

CommaExpr:	COMMA Expr CommaExpr		{ $$ = insertRepetition($2, $3); }  
		|								{ $$ = NULL; }
		; 

%%

int main(int argc, char **argv)
{
	line = 1;
	col = 1;
	int i;

	if(yyparse() == 0)
	{
		int show_ast = 0, show_table = 0;

		for(i = 0; i < argc; i++)
		{
			if(strcmp(argv[i], "-t") == 0)
				show_ast = 1;
			
			if(strcmp(argv[i], "-s") == 0)
				show_table = 1;
		}	

		if(show_ast == 1 && myProgram != NULL)
			printAST(myProgram, 0);
		/*	
		mySemantic = check_program(myProgram);	
		
		if(show_table == 1)	
			show_tables(mySemantic);
		*/
	}
	else
		printf("\nParsing not sucessfull\n");
	
	return 0;
}

void yyerror(char* s)
{
	if(strcmp(yytext, "") == 0)
		printf("Line %d, col %d: %s: %s\n", line, col, s, yytext);
	else
		printf("Line %d, col %d: %s: %s\n", line, col - yyleng, s, yytext);
	
	exit(0);
}

