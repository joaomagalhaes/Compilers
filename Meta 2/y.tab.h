/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OP1 = 258,
     OP2 = 259,
     OP3 = 260,
     OP4 = 261,
     ID = 262,
     INTLIT = 263,
     BOOLLIT = 264,
     INT = 265,
     BOOL = 266,
     NEW = 267,
     IF = 268,
     ELSE = 269,
     WHILE = 270,
     PRINT = 271,
     PARSEINT = 272,
     CLASS = 273,
     RESERVED = 274,
     PUBLIC = 275,
     STATIC = 276,
     VOID = 277,
     STRING = 278,
     DOTLENGTH = 279,
     RETURN = 280,
     OCURV = 281,
     CCURV = 282,
     OBRACE = 283,
     CBRACE = 284,
     OSQUARE = 285,
     CSQUARE = 286,
     NOT = 287,
     ASSIGN = 288,
     SEMIC = 289,
     COMMA = 290
   };
#endif
/* Tokens.  */
#define OP1 258
#define OP2 259
#define OP3 260
#define OP4 261
#define ID 262
#define INTLIT 263
#define BOOLLIT 264
#define INT 265
#define BOOL 266
#define NEW 267
#define IF 268
#define ELSE 269
#define WHILE 270
#define PRINT 271
#define PARSEINT 272
#define CLASS 273
#define RESERVED 274
#define PUBLIC 275
#define STATIC 276
#define VOID 277
#define STRING 278
#define DOTLENGTH 279
#define RETURN 280
#define OCURV 281
#define CCURV 282
#define OBRACE 283
#define CBRACE 284
#define OSQUARE 285
#define CSQUARE 286
#define NOT 287
#define ASSIGN 288
#define SEMIC 289
#define COMMA 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 22 "ijparser.y"
{
	char* string;
	is_node* node;
}
/* Line 1529 of yacc.c.  */
#line 124 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

