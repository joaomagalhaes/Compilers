#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "structures.h"

typedef struct _t1
{
	char name[64];		// element name
	char type[64];		// element type
	int param; 			// 1 is a param, 0 isnt
	struct _t1 *next;
} table_element;


typedef struct _t4
{
	char name[64]; 	   // method name
	char type[64];	   // method type
	struct _t4 *next;  
	table_element *locals; // lista elementos do metodo
} environment_list;


typedef struct _t5
{
	table_element* global;
	environment_list* methods;
} prog_env;

void show_tables(prog_env* program);
table_element *insert_element(char *ele_name, char* ele_type, int ele_par);
environment_list *insert_method(char *name, char *type);

#endif
