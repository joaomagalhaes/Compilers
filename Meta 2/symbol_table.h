#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "structures.h"

typedef struct _t1
{
	char id[64];		// element name (eg. 'numberOfCoins')
	node_type type;		// element type
	int param; 			// 0 - no param , 1 - param
	int array_size; 	// size if its an array, (eg. String[10] -> 10)
	
	struct _t1 *next;	// next element
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
	environment_list* methods;
} prog_env;

void show_tables(prog_env* program);
table_element *insert_element(char *ele_name, node_type ele_type, int ele_par, int ele_array_size);
environment_list *insert_method(char *name, char *type);

/*
table_element *insert_el(char *str, char *str2, node_type t, int count, node_type  par, char *fu, char* pai, int npar);
table_element *insertInFunction(table_element *newSymbol, char *fu, char *type, char *pai, int npar);
int checkFuncDef(char *fu);
*/

#endif
