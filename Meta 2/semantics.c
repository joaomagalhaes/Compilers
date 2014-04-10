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
                    "Null" };

prog_env *check_program(is_node *node)
{
	prog_env *prog = (prog_env*) malloc(sizeof(prog_env));
	prog->global = NULL;
	prog->methods = NULL;

	if(node->type == Program)
	{
		printf("no 'Program' encontrado\n");
		check_class(node->child, prog);
	
	} else
		printf("no 'Program' nao encontrado\n");
	
	return prog;
}

void check_class(is_node *node, prog_env *prog)
{
	while(node != NULL)
	{
		if(node->id)
			printf("Encontrado no '%s' do tipo '%s'\n", node->id, sem_type[node->type]);
		else
			printf("Encontrado no do tipo '%s' sem id\n", sem_type[node->type]);

		switch(node->type)
		{
			case Id: // nome da classe
				printf("no 'Id' encontrado\n");
				prog->global = insert_element(node->id, node->type, 0, 0);
				printf("no 'Id' inserido na tabela\n");
				break;

			case VarDecl:
				printf("no 'VarDecl' encontrado\n");
				prog->global->next = insert_element(node->id, node->type, 0, 0);
				check_type(node->child);
				break;

			case MethodDecl:
				check_type(node->child);
				break;
				
			default:
				break;

		}
		node = node->next;
	}
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

