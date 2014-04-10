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
                    "Null" };
			
void show_tables(prog_env* program)
{
	table_element* class;

	printf("===== Class %s Symbol Table =====\n", program->global->id);

	printf("a imprimir tabela de simbolos global\n");

	printf("a imprimir tabela de simbolos de cada metodo\n");
}

table_element *insert_element(char *ele_name, node_type ele_type, int ele_par, int ele_array_size)
{

	//printf("breakpoint - 1\n");
	table_element *new_symbol = (table_element* ) malloc(sizeof(table_element));
	//printf("breakpoint - 2\n");
	strcpy(new_symbol->id, ele_name);
	//printf("breakpoint - 3\n");
	new_symbol->type = ele_type;
	//printf("breakpoint - 4\n");
	new_symbol->param = ele_par;
	//printf("breakpoint - 5\n");
	new_symbol->array_size = ele_array_size;
	//printf("breakpoint - 6\n");
	new_symbol->next = NULL;
	//printf("breakpoint - 7\n");
	return new_symbol;
}


/*
table_element *insert_element(char *str, Node_type type, int count, char *a_size, int offset, int marker)
{
	int i;
	table_element *nSymbol = (table_element *)malloc(sizeof(table_element));
	//printf("%s\n", tk[type]);
	if(type == FuncDeclaration || type == FuncDefinition)
	{
		//printf("Recebe funcDeclarator\n");
		strcpy(nSymbol->name, str);
		strcpy(nSymbol->type_def, "function");
		nSymbol->next = NULL;
		nSymbol->offset = offset;
		nSymbol->type = type;
	}
	else{
		//table_element *aux;
		//table_element *previous;
		
		strcpy(nSymbol->name, str);
		nSymbol->type = type;
		nSymbol->ast = count;
		nSymbol->a_size = a_size;
		
		strcpy(nSymbol->type_def, tk[nSymbol->type]);
		for(i = 0; i < count; i++)
		{
			sprintf(nSymbol->type_def,"%s%s", nSymbol->type_def, "*");
		}
		
		if(a_size){
			sprintf(nSymbol->type_def,"%s[%s]", nSymbol->type_def, a_size);
		}
		nSymbol->next = NULL;
	}

	nSymbol->marker = marker;
	return nSymbol;
}
*/


