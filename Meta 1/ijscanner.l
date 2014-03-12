
%{  
	/* Joao Andre Pedro 2009112620 
	   Joao David Magalhaes 2009112796 */
%}

%x COMMENT

%{
#include <stdio.h>
#include <stdlib.h>
int line = 1;
int col = 1;
%}

%%

%{  
	/* iJava tokens */ 
%}
"true"|"false"					{ col += yyleng; printf("BOOLLIT(%s)\n", yytext); }
"int"							{ col += yyleng; printf("INT\n");       }
"boolean"						{ col += yyleng; printf("BOOL\n");      }
"new"							{ col += yyleng; printf("NEW\n");       }
"if"							{ col += yyleng; printf("IF\n");        }
"else"							{ col += yyleng; printf("ELSE\n");      }
"while" 	    				{ col += yyleng; printf("WHILE\n");     }
"System.out.println"			{ col += yyleng; printf("PRINT\n");     }
"Integer.parseInt"				{ col += yyleng; printf("PARSEINT\n");  }
"class"							{ col += yyleng; printf("CLASS\n");     }
"public"						{ col += yyleng; printf("PUBLIC\n");    }
"static"						{ col += yyleng; printf("STATIC\n");    }
"void"							{ col += yyleng; printf("VOID\n");      }
"String"						{ col += yyleng; printf("STRING\n");    }
".length"						{ col += yyleng; printf("DOTLENGTH\n"); }
"return"						{ col += yyleng; printf("RETURN\n");    }
"("								{ col += yyleng; printf("OCURV\n");     }
")"								{ col += yyleng; printf("CCURV\n");     }
"{"								{ col += yyleng; printf("OBRACE\n");    }
"}"								{ col += yyleng; printf("CBRACE\n");    }
"["								{ col += yyleng; printf("OSQUARE\n");   }
"]"								{ col += yyleng; printf("CSQUARE\n");   }
"&&"|"||"						{ col += yyleng; printf("OP1(%s)\n", yytext);  }
"<"|">"|"=="|"!="|"<="|">="		{ col += yyleng; printf("OP2(%s)\n", yytext);  }
"+"|"-"							{ col += yyleng; printf("OP3(%s)\n", yytext);  }
"*"|"/"|"%"						{ col += yyleng; printf("OP4(%s)\n", yytext);  }
"!"								{ col += yyleng; printf("NOT\n");       }
"="								{ col += yyleng; printf("ASSIGN\n");    }
";"								{ col += yyleng; printf("SEMIC\n");     }
","								{ col += yyleng; printf("COMMA\n");     }

%{  
	/* Java reserved tokens */
%}
"abstract"						{ col += yyleng; printf("RESERVED\n"); }
"continue"						{ col += yyleng; printf("RESERVED\n"); }	
"for"							{ col += yyleng; printf("RESERVED\n"); }
"switch"						{ col += yyleng; printf("RESERVED\n"); }
"assert"						{ col += yyleng; printf("RESERVED\n"); }
"default"						{ col += yyleng; printf("RESERVED\n"); }
"goto"							{ col += yyleng; printf("RESERVED\n"); }
"package"						{ col += yyleng; printf("RESERVED\n"); }
"synchronized"					{ col += yyleng; printf("RESERVED\n"); }
"do"							{ col += yyleng; printf("RESERVED\n"); }
"private"						{ col += yyleng; printf("RESERVED\n"); }
"this"							{ col += yyleng; printf("RESERVED\n"); }
"break"							{ col += yyleng; printf("RESERVED\n"); }
"double"						{ col += yyleng; printf("RESERVED\n"); }
"implements"					{ col += yyleng; printf("RESERVED\n"); }
"protected"						{ col += yyleng; printf("RESERVED\n"); }
"throw"							{ col += yyleng; printf("RESERVED\n"); }
"byte"							{ col += yyleng; printf("RESERVED\n"); }
"import"						{ col += yyleng; printf("RESERVED\n"); }
"throws"						{ col += yyleng; printf("RESERVED\n"); }
"case"							{ col += yyleng; printf("RESERVED\n"); }
"enum"							{ col += yyleng; printf("RESERVED\n"); }
"instanceof"					{ col += yyleng; printf("RESERVED\n"); }
"transient"						{ col += yyleng; printf("RESERVED\n"); }
"catch"							{ col += yyleng; printf("RESERVED\n"); }
"extends"						{ col += yyleng; printf("RESERVED\n"); }
"short"							{ col += yyleng; printf("RESERVED\n"); }
"try"							{ col += yyleng; printf("RESERVED\n"); }
"char"							{ col += yyleng; printf("RESERVED\n"); }
"final"							{ col += yyleng; printf("RESERVED\n"); }
"interface"						{ col += yyleng; printf("RESERVED\n"); }
"finally"						{ col += yyleng; printf("RESERVED\n"); }
"long"							{ col += yyleng; printf("RESERVED\n"); }
"strictfp"						{ col += yyleng; printf("RESERVED\n"); }
"volatile"						{ col += yyleng; printf("RESERVED\n"); }
"const"							{ col += yyleng; printf("RESERVED\n"); }
"float"							{ col += yyleng; printf("RESERVED\n"); }
"native"						{ col += yyleng; printf("RESERVED\n"); }
"super"							{ col += yyleng; printf("RESERVED\n"); }

%{  
	/* IDs and INTLITs */
%}
[a-zA-Z_$][a-zA-Z0-9_$]*		{ col += yyleng; printf("ID(%s)\n", yytext); }
[0-9]+|"0x"[a-fA-F0-9]+			{ col += yyleng; printf("INTLIT(%s)\n", yytext);  }

%{  
	/* comments handler */
%}
"//".*							;
"/*"							{ BEGIN COMMENT; }
<COMMENT>.						;
<COMMENT>"\n"					{ line++; col = 1; }
<COMMENT><<EOF>>				{ printf("Line %d, col %d: unterminated comment\n", line, col + 1); col += yyleng; }
<COMMENT>"*/"					{ BEGIN 0; }

%{  
	/* other stuff */
%}
"\n"						{ line++; col = 1; } 
[ \t\f\r]					{ col += yyleng; }
.							{ printf("Line %d, col %d: illegal character ('%c')\n", line, col + 1, yytext[0]); col += yyleng; }

%%

int main()
{
	yylex();
}

int yywrap()
{
	return 1;
}

