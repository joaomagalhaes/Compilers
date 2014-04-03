#include "functions.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Start

// Program
is_node *insertProgram(is_node *id, is_node *fieldsmethods)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));
	
	node->child = id;
	if(fieldsmethods!= NULL)
		id->next = fieldsmethods;

	node->next = NULL;
	node->type = Program;
	node->id = NULL;

	return node;
}

// FieldMethodDecl

// FieldDecl

// MethodDecl
is_node *insertMethodDecl(is_node *type, is_node *id, is_node *params, is_node *varDecl, is_node *stats)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));

	// adicionar tipo e id do metodo
    node->child = type;
    type->next = id;

    // adicionar parametros do metodo
    int changes = 0;
    if(params != NULL) 
    {
    	id->next = params;
    	changes = 1;
	}

	// se changes = 1 existem parametros
	// adicionar declaracoes de variaveis do metodo
	if(varDecl != NULL || stats != NULL)
	{
		is_node *methodBody = (is_node*) malloc(sizeof(is_node));
		methodBody->type = MethodBody;
		methodBody->id = NULL;
		methodBody->next = NULL;

		if(varDecl != NULL && changes == 1)
		{
			params->next = methodBody;
			methodBody->child = varDecl;
			changes = 2;

		} else if(varDecl != NULL)
		{
			id->next = methodBody;
			methodBody->child = varDecl;
			changes = 2;
		}

		// adicionar statements
		if(stats != NULL && changes == 1)
		{
			params->next = methodBody;
			methodBody->child = stats;

		}else if(stats != NULL && changes == 2)
		{
			varDecl->next = stats;

		}else if(stats != NULL)
		{
			id->next = methodBody;
			methodBody->child = stats;
		}

		node->next = NULL;
		node->type = MethodDecl;
		node->id = NULL;

	} 
    return node;
}

// MethodVarDecl

// FormalParams
is_node *insertFormalParams1(is_node *type, is_node *id)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));
	is_node *MethodParamsnode = (is_node*) malloc(sizeof(is_node));

	node->child = type;
	type->next = id;

	node->type = ParamDeclaration;
	node->id = NULL;
		
	MethodParamsnode->child = node;
	MethodParamsnode->next = NULL;
	MethodParamsnode->id = NULL;
	MethodParamsnode->type = MethodParams;

	return MethodParamsnode;	
}


is_node *insertFormalParams2(is_node *type, is_node *id, is_node *moreNodes)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));
	is_node *MethodParamsnode = (is_node*) malloc(sizeof(is_node));

	node->child = type;
	type->next = id;

	node->type = ParamDeclaration;
	node->id = NULL;

	if(moreNodes != NULL)
		node->next=moreNodes;
		
	MethodParamsnode->child = node;
	MethodParamsnode->next = NULL;
	MethodParamsnode->id = NULL;
	MethodParamsnode->type = MethodParams;

	return MethodParamsnode;	
}

// CommaTypeID
is_node *insertFPRepetition(is_node *type, is_node *id)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));

	node->child = type;
	type->next = id;

	node->type = ParamDeclaration;
	node->id = NULL;

	return node;
}

// VarDecl

// CommaID
is_node *insertVarDecl(is_node *type, is_node *id, is_node *moreIDS)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));
	
	node->child = type;
	type->next = id;

	if(moreIDS != NULL)
		id->next = moreIDS;

	node->type = VarDecl;
	node->id = NULL;

	return node;
}

// Type

// Statement
is_node *insertST_if_else(is_node *expr, is_node *stat, is_node *stat2)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));

	node->child = expr;

	int change = 0;
	if(stat != NULL) 
	{
		expr->next = stat;
		change = 1;
	}

	if(stat2 != NULL && change == 1)
		stat->next = stat2;
	else
		expr->next = stat2;

	node->type = IfElse;
	node->id = NULL;

	return node;
}

is_node *insertST_ret_exp_sem(is_node *expr)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));

	node->child = expr;
	node->next = NULL;
	node->type = Return;
	node->id = NULL;

	return node;
}

// StatRep

// Exp


// Auxs

is_node *insert_ID(char* str)
{
	is_node *node = (is_node*) malloc(sizeof(is_node));

	node->child = NULL;
	node->next = NULL; 
	node->type = Id;
	node->id = str;
	
	return node;
}

is_node *insert_INTLIT(char* str)
{
	is_node *node = (is_node*) malloc (sizeof(is_node));

	node->child = NULL;
	node->next = NULL;
	node->type = IntLit;
	node->id = str;

	return node;
}

is_node *insertType(node_type type)
{
    is_node *node = (is_node*) malloc(sizeof(is_node));
    node->child = NULL;
    node->next = NULL;
    node->id = NULL;
    node->type = type;

    return node;
}

is_node *insertRepetition(is_node *x, is_node *y)
{
	if(x->next == NULL)
		x->next = y;
    else
	{ 
		y->next=x->next;	
		x->next = y;
	}

    return x;
}









