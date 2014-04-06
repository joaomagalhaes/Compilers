#include "structures.h"
#include "semantics.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern is_node *myProgram;
extern prog_env *mySemantic;

char* sem_type[] = {   "Program",
                    "VarDecl",
                    "MethodDecl", "MethodParams", "MethodBody", "ParamDeclaration",
                    "CompoundStat", "IfElse", "Print", "Return", "Store", "StoreArray", "While",
                    "Or", "And", "Eq", "Neq", "Lt", "Gt", "Leq", "Geq", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Length", "LoadArray", "Call", "NewInt", "NewBool", "ParseArgs",
                    "Int", "Bool", "IntArray", "BoolArray", "StringArray", "Void", "Id", "IntLit", "BoolLit",
                    "Null" };

int check_program(is_node *node)
{
	if(node->type == Program)
		check_class(node->child);
	else
		printf("erro - node 'Program' nao encontrado\n");
	
	return 0;
}

void check_class(is_node *node)
{
	while(node != NULL)
	{
		if(node->type == VarDecl)
			check_type(node->child);
		
		else if(node->type == MethodDecl)
			check_type(node->child);
		
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

