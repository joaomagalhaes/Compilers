
#include "structures.h"
#include "shows.h"
#include <stdlib.h>
#include <stdio.h>

char* types[] = {	"Program",
					"VarDecl", 
					"MethodDecl", "MethodParams", "MethodBody", "ParamDeclaration",  
					"CompoundStat", "IfElse", "Print", "Return", "Store", "StoreArray", "While",
					"Or", "And", "Eq", "Neq", "Lt", "Gt", "Leq", "Geq", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Length", "LoadArray", "Call", "ParseArgs",
					"Int", "Bool", "IntArray", "BoolArray", "StringArray", "Void", "Id", "IntLit", "BoolLit",
 				    "Null" };

void printAST(is_node* node, int tabs)
{
	int i;
	for(i = 0; i < tabs; i++)
		printf("  ");
	
	if(node->id)
		printf("%s(%s)\n", types[node->type], node->id);
	else
		printf("%s\n", types[node->type]);

	if(node->child)
		printAST(node->child, tabs + 1);
	
	if(node->next)
		printAST(node->next, tabs);
}