#include "structures.h"
#include "symbol_table.h"
//#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern prog_env* mySemantic;

char* st_types[] = {   "Program",
                    "VarDecl",
                    "MethodDecl", "MethodParams", "MethodBody", "ParamDeclaration",
                    "CompoundStat", "IfElse", "Print", "Return", "Store", "StoreArray", "While",
                    "Or", "And", "Eq", "Neq", "Lt", "Gt", "Leq", "Geq", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Length", "LoadArray", "Call", "NewInt", "NewBool", "ParseArgs",
                    "Int", "Bool", "IntArray", "BoolArray", "StringArray", "Void", "Id", "IntLit", "BoolLit",
                    "Null", "NoNode", "method" };
			
void show_tables(prog_env* program)
{
	table_element* ele = program->global;
	table_element *aux;
	environment_list* env_l = program->methods;

	printf("===== Class %s Symbol Table =====\n", ele->id);
	ele = ele->next;	
	aux = ele;
	while(aux != NULL)
	{
		printf("%s\t%s\n", aux->id, st_types[aux->type]);
		aux=aux->next;
	}
	/*	
	while(env_l != NULL)
	{
		printf("===== Method %s Symbol Table =====\n", env_l->name);
		env_l = env_l->next;

		table_element *aux_local=env_l->locals;
		while(aux_local != NULL)
		{	
		//	printf("%s\t%s", aux_local->id, st_types[aux_local->type]);
			if(aux_local->param==1)
				printf("\tparam\n");
			else
				printf("\n");
			
			aux_local=aux_local->next;
		}
	}
	*/
}

table_element *insert_element(char *ele_name, node_type ele_type, int ele_par, int ele_array_size)
{
	table_element *new_symbol = (table_element* ) malloc(sizeof(table_element));
	strcpy(new_symbol->id, ele_name);
	new_symbol->type = ele_type;
	new_symbol->param = ele_par;
	new_symbol->array_size = ele_array_size;
	new_symbol->next = NULL;
	return new_symbol;
}

environment_list *insert_method(char *name, char *type)
{
	//printf(">>>>>> nome da metodo: %s", name);
	environment_list *new_list = (environment_list*) malloc(sizeof(environment_list));
	strcpy(new_list->name, name);
	strcpy(new_list->tipo, type);
	new_list->next = NULL;
	return new_list;
}

