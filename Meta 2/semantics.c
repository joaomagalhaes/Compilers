#include "structures.h"
#include "semantics.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* sem_type[] = {   "Program",
                    "VarDecl",
                    "MethodDecl", "MethodParams", "MethodBody", "ParamDeclaration",
                    "CompoundStat", "IfElse", "Print", "Return", "Store", "StoreArray", "While",
                    "Or", "And", "Eq", "Neq", "Lt", "Gt", "Leq", "Geq", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Length", "LoadArray", "Call", "NewInt", "NewBool", "ParseArgs",
                    "Int", "Bool", "IntArray", "BoolArray", "StringArray", "Void", "Id", "IntLit", "BoolLit",
                    "Null", "method" };

prog_env *check_program(is_node *node)
{
	prog_env *prog = (prog_env*) malloc(sizeof(prog_env));
	prog->global = NULL;
	prog->methods = NULL;

	if(node->type == Program)
		check_class(node->child, prog);
	
	return prog;
}

void check_class(is_node *node, prog_env *prog)
{
	table_element *new;
	environment_list *new_l;
	table_element *prog_aux;
	environment_list* env_aux = NULL;

	while(node != NULL)
	{	
		switch(node->type)
		{
			case Id: // nome da classe
				prog->global = insert_element(node->id, node->type, 0, 0);
				break;

			case VarDecl:
				prog_aux = prog->global;
				new = insert_element(node->child->next->id, node->child->type, 0, 0);
				
				while(prog_aux->next != NULL)
					prog_aux = prog_aux->next;

				prog_aux->next = new;	
				break;

			case MethodDecl:
				prog_aux = prog->global;
				new = insert_element(node->child->next->id, (node_type) method, 0, 0);
				
				while(prog_aux->next != NULL)
					prog_aux = prog_aux->next;

				prog_aux->next = new;	

				// -------

				env_aux = prog->methods;
				new_l = insert_method(node->child->next->id, sem_type[node->child->type] );
				if(env_aux == NULL)
					prog->methods = new_l;
			
				else
				{
					while(env_aux->next != NULL)
						env_aux = env_aux->next;

					env_aux->next = new_l;	
				}
				
				//check_methodDecl();
				break;
				
			default:
				break;

		}
		node = node->next;
	}
}

void insert_global_table()
{
	table_element *new;

}

void check_type(is_node *node)
{
	while(node != NULL)
	{
		if(node->type == Int)
			printf("descoberto int\n");
	
		node = node->next;
	}
}

