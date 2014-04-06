#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "structures.h"

typedef struct _t1
{
	char name[64];
	char tipo[64];
	char *par;
	node_type type;
	struct _t1 *next;
} table_element;


typedef struct _t4
{
	char name[64];
	char tipo[64];
	int FuncDefined; //1 declarada, 2 definida
	int chamada;
	int nargs;
	struct _t4 *next;
	table_element *locals;
} environment_list;


typedef struct _t5
{
	table_element* global;
	environment_list* procs;
} prog_env;

table_element *insert_el(char *str, char *str2, node_type t, int count, node_type  par, char *fu, char* pai, int npar);
table_element *insertInFunction(table_element *newSymbol, char *fu, char *type, char *pai, int npar);
int checkFuncDef(char *fu);

#endif
