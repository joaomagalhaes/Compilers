
%{  
	/* Joao Andre Pedro 2009112620 
	   Joao David Magalhaes 2009112796 */
%}

%x COMMENT

%{
#include "structures.h"
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

int line = 1, col = 1, lineAux, colAux;
%}

%%

"true"|"false"					{ col += yyleng; yylval.string = (char*) strdup(yytext); return BOOLLIT; }
"int"							{ col += yyleng; return INT; }
"boolean"						{ col += yyleng; return BOOL; }
"new"							{ col += yyleng; return NEW; }
"if"							{ col += yyleng; return IF; }
"else"							{ col += yyleng; return ELSE; }
"while" 	    				{ col += yyleng; return WHILE; }
"System.out.println"			{ col += yyleng; return PRINT; }
"Integer.parseInt"				{ col += yyleng; return PARSEINT; }
"class"							{ col += yyleng; return CLASS; }
"public"						{ col += yyleng; return PUBLIC; }
"static"						{ col += yyleng; return STATIC; }
"void"							{ col += yyleng; return VOID; }
"String"						{ col += yyleng; return STRING; }
".length"						{ col += yyleng; return DOTLENGTH; }
"return"						{ col += yyleng; return RETURN; }
"("								{ col += yyleng; return OCURV; }
")"								{ col += yyleng; return CCURV; }
"{"								{ col += yyleng; return OBRACE; }
"}"								{ col += yyleng; return CBRACE; }
"["								{ col += yyleng; return OSQUARE; }
"]"								{ col += yyleng; return CSQUARE; }
"&&"|"||"						{ col += yyleng; yylval.string = (char*) strdup(yytext); return OP1; }
"<"|">"|"=="|"!="|"<="|">="		{ col += yyleng; yylval.string = (char*) strdup(yytext); return OP2; }
"+"|"-"							{ col += yyleng; yylval.string = (char*) strdup(yytext); return OP3; }
"*"|"/"|"%"						{ col += yyleng; yylval.string = (char*) strdup(yytext); return OP4; }
"!"								{ col += yyleng; return NOT; }
"="								{ col += yyleng; return ASSIGN; }
";"			   					{ col += yyleng; return SEMIC; }
","								{ col += yyleng; return COMMA; }

"abstract"						{ col += yyleng; return RESERVED; }
"continue"						{ col += yyleng; return RESERVED; }	
"for"							{ col += yyleng; return RESERVED; }
"switch"						{ col += yyleng; return RESERVED; }
"assert"						{ col += yyleng; return RESERVED; }
"default"						{ col += yyleng; return RESERVED; }
"goto"							{ col += yyleng; return RESERVED; }
"package"						{ col += yyleng; return RESERVED; }
"synchronized"					{ col += yyleng; return RESERVED; }
"do"							{ col += yyleng; return RESERVED; }
"private"						{ col += yyleng; return RESERVED; }
"this"							{ col += yyleng; return RESERVED; }
"break"							{ col += yyleng; return RESERVED; }
"double"						{ col += yyleng; return RESERVED; }
"implements"					{ col += yyleng; return RESERVED; }
"protected"						{ col += yyleng; return RESERVED; }
"throw"							{ col += yyleng; return RESERVED; }
"byte"							{ col += yyleng; return RESERVED; }
"import"						{ col += yyleng; return RESERVED; }
"throws"						{ col += yyleng; return RESERVED; }
"case"							{ col += yyleng; return RESERVED; }
"enum"							{ col += yyleng; return RESERVED; }
"instanceof"					{ col += yyleng; return RESERVED; }
"transient"						{ col += yyleng; return RESERVED; }
"catch"							{ col += yyleng; return RESERVED; }
"extends"						{ col += yyleng; return RESERVED; }
"short"							{ col += yyleng; return RESERVED; }
"try"							{ col += yyleng; return RESERVED; }
"char"							{ col += yyleng; return RESERVED; }
"final"							{ col += yyleng; return RESERVED; }
"interface"						{ col += yyleng; return RESERVED; }
"finally"						{ col += yyleng; return RESERVED; }
"long"							{ col += yyleng; return RESERVED; }
"strictfp"						{ col += yyleng; return RESERVED; }
"volatile"						{ col += yyleng; return RESERVED; }
"const"							{ col += yyleng; return RESERVED; }
"float"							{ col += yyleng; return RESERVED; }
"native"						{ col += yyleng; return RESERVED; }
"super"							{ col += yyleng; return RESERVED; }
"null"							{ col += yyleng; return RESERVED; }
"--"							{ col += yyleng; return RESERVED; }
"++"							{ col += yyleng; return RESERVED; }

[a-zA-Z_$][a-zA-Z0-9_$]*		{ col += yyleng; yylval.string = (char*) strdup(yytext); return ID; }
[0-9]+|0x[a-fA-F0-9]+			{ col += yyleng; yylval.string = (char*) strdup(yytext); return INTLIT; }

"//".*							;
"/*"							{ BEGIN COMMENT; lineAux = line; colAux = col; }
<COMMENT>.						{ col += yyleng; }
<COMMENT>"\n"					{ line++; col = 1; }
<COMMENT><<EOF>>				{ printf("Line %d, col %d: unterminated comment\n", lineAux, colAux); return 0; }
<COMMENT>"*/"					{ BEGIN 0; col += 2; }

"\n"							{ line++; col = 1; } 
[ \t\f\r]						{ col += yyleng; }
.								{ printf("Line %d, col %d: illegal character ('%c')\n", line, col, yytext[0]); col += yyleng; }

<<EOF>>							{ yyterminate(); }

%%

int yywrap()
{
	return 1;
}

