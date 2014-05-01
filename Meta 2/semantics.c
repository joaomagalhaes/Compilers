#include "structures.h"
#include "semantics.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* sem_type[] = {    "Program",
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
		check_class(node->child, prog);
	
	return prog;
}

void check_class(is_node *node, prog_env *prog)
{
    is_node* aux;
    char* aux_type;
    
	while(node != NULL)
	{	
		switch(node->type)
		{
			case Id: // nome da classe - inserir tabela global
				insert_global_table(prog, node->id, "");
				break;

			case VarDecl: // variaveis globais - inserir tabela global
				
                aux_type = sem_type[node->child->type];
                aux = node->child->next;
                while(aux != NULL)
                {
                    insert_global_table(prog, aux->id, aux_type);
                    aux = aux->next;
                }
                break;

			case MethodDecl: // declaracoes de metodos
				// inserir tabela global
				insert_global_table(prog, node->child->next->id, "method");
				
				// insere metodos na tabela methods
				insert_methods_table(prog, node->child->next->id, sem_type[node->child->type] );
				
				check_methodDecl(prog, node->child);
				break;
				
			default:
				break;

		}
		node = node->next;
	}
}

void check_methodDecl(prog_env* prog, is_node* node)
{
    char* method_name = node->next->id;
    
    insert_method_elements(prog, method_name, sem_type[node->type], "return", 0);
    
    while(node != NULL)
    {
        switch(node->type)
        {
            case MethodParams:
                check_methodParams(prog, method_name, node->child);
                break;
            
            case MethodBody:
                check_methodBody(prog, method_name, node->child);
                break;
                
            default:
                break;
        }
        node = node->next;
    }
}

void check_methodBody(prog_env* prog, char* name, is_node* node)
{
    is_node* aux;
    while(node != NULL)
    {
        if(node->type == VarDecl)
        {
            char* type_aux = sem_type[node->child->type];
            aux = node->child->next;
            while(aux != NULL)
            {
                insert_method_elements(prog, name, type_aux, aux->id, 0);
                aux = aux->next;
            }
        }
        
        node = node->next;
    }
}

void check_methodParams(prog_env* prog, char* name, is_node* node)
{
    while(node != NULL)
    {
        insert_method_elements(prog, name, sem_type[node->child->type], node->child->next->id, 1);
        node = node->next;
    }
}

void insert_method_elements(prog_env* prog, char* method_name, char* type, char* name, int par)
{
    /*
    if(par == 1)
        printf("vou inserir no metodo %s, o parametro %s, do tipo %s\n", method_name, name, type);
    else
        printf("vou inserir no metodo %s, a variavel %s, do tipo %s\n", method_name, name, type);
    */
    environment_list* methods = prog->methods;

    while(methods != NULL)
    {
        if(strcmp(methods->name, method_name) == 0)
        {
            table_element* method_element = methods->locals;
            table_element* prev = methods->locals;

            if(methods->locals == NULL)
                methods->locals = insert_element(name, type, par);
            
            else
            {
                while(method_element != NULL)
                {
                    prev = method_element;
                    method_element = method_element->next;
                }
                prev->next = insert_element(name, type, par);
            }
        }
        methods = methods->next;
    }
}

void insert_methods_table(prog_env* prog, char* id, char* type)
{
	environment_list* temp;
	temp = prog->methods;
	
	if(prog->methods == NULL)
		prog->methods = insert_method(id, type);
	
	else
	{
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = insert_method(id, type);
	}
}

void insert_global_table(prog_env* prog, char* id, char* type)
{
	table_element* temp;
	temp = prog->global;
	
	if(prog->global == NULL)
		prog->global = insert_element(id, type, 0);
	
	else
	{
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = insert_element(id, type, 0);
	}
}

