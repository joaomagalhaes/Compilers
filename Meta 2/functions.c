#include "functions.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
is_node *insertStart(is_node *x)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));
	
	node->child = x;
	node->next = NULL;

	node->type = Program;
	node->id = NULL;
	
	return node;
}
 
is_node *insertProgram(is_node *x)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));
	
	node->child = x;
	node->next = NULL;

	node->type = Program;
	node->id = NULL;
	
	return node;
}

