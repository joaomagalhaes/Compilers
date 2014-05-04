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

/* ************************************
 * Construccao da tabelas de simbolos *
 ************************************ */

// Recebe arvore sintaxe abstracta (no Program)
// Devolve tabela de simbolos
prog_env *check_program(is_node *node)
{
	prog_env *prog = (prog_env*) malloc(sizeof(prog_env));
	prog->global = NULL;
	prog->methods = NULL;

	if(node->type == Program)
		check_class(node->child, prog);
	
	return prog;
}

// Recebe filhos do no 'Program'
// Se Id adicionar nome da classe na tabela de simbolos global
// Se VarDecl adiciona variavel na tabela de simbolos global
// Se MethodDecl adiciona metodo na tabela de simbolos global e cria tabela simbolos do metodo
void check_class(is_node *node, prog_env *prog)
{
    is_node* aux;
    char* aux_type;
    
	while(node != NULL)
	{	
		switch(node->type)
		{
			case Id:
				insert_global_table(prog, node->id, "");
				break;

			case VarDecl:
                aux_type = sem_type[node->child->type];
                aux = node->child->next;
                while(aux != NULL)
                {
                    insert_global_table(prog, aux->id, aux_type);
                    aux = aux->next;
                }
                break;

			case MethodDecl:
				insert_global_table(prog, node->child->next->id, "method");
				insert_methods_table(prog, node->child->next->id, sem_type[node->child->type]);
				
				check_methodDecl(prog, node->child); // verificar filhos do no MethodDecl
				break;
				
			default:
				break;
		}
		node = node->next;
	}
}

// Recebe filhos do no 'MethodDecl'
// Adiciona o elemento return <tipo> na tabela de simbolo do metodo correspondente
// Chama as funcoes de verificacoes dos no filhos (MethodParams e MethodBody)
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

// Recebe filhos do no 'MethodBody'
// Se VarDecl adiciona a variavel na tabela de simbolos do metodo correspondente
void check_methodBody(prog_env* prog, char* name, is_node* node)
{
    is_node* aux;
    char* type_aux;
    
    while(node != NULL)
    {
        switch (node->type)
        {
            case VarDecl:
                
                type_aux = sem_type[node->child->type];
                aux = node->child->next;
                while(aux != NULL)
                {
                    insert_method_elements(prog, name, type_aux, aux->id, 0);
                    aux = aux->next;
                }
                break;

            default:
                break;
        }
        node = node->next;
    }
}

// Recebe filhos do no 'MethodParams'
// Adiciona os parametros na tabela de simbolos do metodo correspondente
void check_methodParams(prog_env* prog, char* name, is_node* node)
{
    while(node != NULL)
    {
        insert_method_elements(prog, name, sem_type[node->child->type], node->child->next->id, 1);
        node = node->next;
    }
}

// Funcao Auxiliar - insercao na tabela de simbolos global
// Verificao do erro semantico 'Symbol already defined'
void insert_global_table(prog_env* prog, char* id, char* type)
{
	table_element* temp;
	temp = prog->global;
	
	if(prog->global == NULL)
		prog->global = insert_element(id, type, 0);
	
	else
	{
		while(temp->next != NULL)
        {
            check_defined(temp->next->name,id);
			temp = temp->next;
        }
		temp->next = insert_element(id, type, 0);
	}
}

// Funcao Auxiliar - insercao de nova tabela de simbolos de metodo
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

// Funcao Auxiliar - insercao de elemento na tabela de simbolos do metodo correspondente
// Verificao do erro semantico 'Symbol already defined'
void insert_method_elements(prog_env* prog, char* method_name, char* type, char* name, int par)
{
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
                    check_defined(method_element->name,name);
                    prev = method_element;
                    method_element = method_element->next;
                }
                prev->next = insert_element(name, type, par);
            }
        }
        methods = methods->next;
    }
}

/* ************************************
 * Verificacao dos erros semanticos   *
 ************************************ */

// Recebe arvore sintaxe abstracta e tabela de simbolos
// Procura nos MethodBody
void check_semantic(is_node* myProgram, prog_env* mySemantic)
{
    is_node* aux = myProgram->child;
    is_node* aux2;
    char* method_name;
    
    while(aux != NULL) // Percorrer os filhos do no Programa
    {
        if(aux->type == MethodDecl) // Caso seja um MethodDecl
        {
            aux2 = aux->child;
            method_name = aux->child->next->id;
            printf("estou no metodo de nome %s\n", method_name);
            
            while(aux2 != NULL)
            {
                if(aux2->type == MethodParams)
                    check_methodParams_sem(mySemantic, method_name, aux2->child);
                else if(aux2->type == MethodBody)
                    check_methodBody_sem(mySemantic, method_name, aux2->child);
                
                aux2 = aux2->next;
            }
        }
        aux = aux->next;
    }
}

// Recebe filhos do no 'MethodBody'
// Caso sejam Store verifica se tipos sao incompativeis
void check_methodBody_sem(prog_env* prog, char* name, is_node* node)
{
    printf("entrei\n");
    is_node* aux;
    char* type_aux;
    
    while(node != NULL)
    {
        if(node->type == Store)
        {
            check_store(node->child, prog, name);
            check_incompatible_assignment(node->child, prog, name);
        }
        node = node->next;
    }
}

void check_methodParams_sem(prog_env* prog, char* name, is_node* node)
{}



// recebe um no Store, verifica se os tipos sao compativeis
void check_incompatible_assignment(is_node *store, prog_env* prog, char* methodName)
{
    printf("a verificar compatibilidade entre a variavel %s e o objeto com o tipo %s\n", store->id, sem_type[store->next->type]);

    // procura a variavel nos globais
    table_element* global;
    global = prog->global;
    
    while(global != NULL)
    {
        if(strcmp(global->name, store->id) == 0)
        {
            if(global->type != sem_type[store->next->type])
            {
                printf("Incompatible type in assigment to %s (got %s, required %s)\n", store->id, sem_type[store->next->type], global->type);
                exit(0);
            }
        }
        
        global = global->next;
    }
    
    // procura a variavel no metodo
    environment_list* methods = prog->methods;
    
    while(methods != NULL)
    {
        if(strcmp(methods->name, methodName) == 0)
        {
            table_element* method_element = methods->locals;
            
            while(method_element != NULL)
            {
                if(strcmp(method_element->name, store->id) == 0)
                {
                    if(method_element->type != sem_type[store->next->type])
                    {
                        printf("Incompatible type in assigment to %s (got %s, required %s)\n", store->id, sem_type[store->next->type], method_element->type);
                        exit(0);
                    }
                }
                method_element = method_element->next;
            }
        }
        methods = methods ->next;
    }
}

void check_defined(char* name, char* nameNew)
{
	if(strcmp(name,nameNew) == 0){
		printf ("Symbol %s already defined\n", name);
		exit(0);
	}
    
}

void check_store(is_node* store, prog_env* prog, char* methodName)
{
	table_element* temp;
	temp = prog->global;
    
	environment_list* aux;
	aux = prog->methods;
	int ver = 0;
	int nparams = -1;
	char* methodCalled;
	
	if(store->next->type == Call){
		
		/*metodo nao declarado*/
		while(temp->next != NULL ){
			if(strcmp(temp->name,store->next->child->id) == 0){
				ver = 1;
				methodCalled=temp->name;
				//break;
			}
			temp = temp->next;
		}
		
		if(ver == 0){
			printf("Cannot find symbol %s\n", store->next->child->id);
			exit(0);
		}
		
		/*parametros nao adequados*/
		//procura metodo (local)
		while(aux!= NULL){
			if(strcmp(aux->name,methodCalled) == 0)
				break;
            
			aux=aux->next;
		}
        
		//tabela simbolos metodo
		table_element* localtemp;
		localtemp = aux->locals;//->child;
        
		//parametros escritos na chamada
		is_node* params = store->next->child->next;
        
		while(params!= NULL){
			nparams ++;
			localtemp=localtemp->next;
			if(localtemp != NULL){
				if (localtemp->param == 1){
					char* paramtype = getType(params->id,prog,methodName);
                    
					//variavel nao declarada
					if(paramtype ==	NULL){
						printf("Cannot find symbol %s\n", params->id);
						exit(0);
					}
                    
					//tipos incompativeis
					if(strcmp(localtemp->type,paramtype)!=0){
						printf("Incompatible type of argument %d in call to method %s (got %s, required %s)\n",nparams,methodCalled,paramtype,localtemp->type);
						exit(0);
					}
                    
				}else{
					//parametros a mais escritos
					printf("Incompatible type of argument %d in call to method %s (got %s, required void)\n",nparams,methodCalled,params->id);
					exit(0);
				}
			}else{
				//parametros a mais escritos
				printf("Incompatible type of argument %d in call to method %s (got %s, required void)\n",nparams,methodCalled,params->id);
				exit(0);
			}
			params=params->next;
		}
        
		int pos;
		//parametros a menos escritos
		if(nparams < (pos=getParamN(prog,methodCalled))){
			
			char* req = getParambyPos(prog,methodCalled,pos);
			printf("Incompatible type of argument %d in call to method %s (got void, required %s)\n",nparams+1,methodCalled, req);
			exit(0);
            
            
		}
        
	}
    
}

//devolve tipo de uma variavel, caso nao exista devolve NULL
char* getType(char* nameP,prog_env* prog,char*methodName)
{
    
	table_element* temp;
	temp = prog->global;
    
	environment_list* aux;
	aux = prog->methods;
    
	//verifica variaveis globais
	while(temp!=NULL){
		if(strcmp(temp->name,nameP)==0)
			return temp->type;
		temp=temp->next;
	}
    
	//verifica variaveis locais do metodo em questao
	while(aux!=NULL){
		if(strcmp(aux->name,methodName)==0){
			table_element* local = aux->locals;
			while(local!=NULL){
				if(strcmp(local->name,nameP)==0)
					return local->type;
				local=local->next;
			}
			return NULL;
		}
		aux=aux->next;
	}
    
	return NULL;
}

//devolve o numero de parametros de um determinado metodo
int getParamN(prog_env* prog,char*called)
{
    
	environment_list* aux;
	aux = prog->methods;
	int param=-1;
	//verifica variaveis locais do metodo em questao
	while(aux!=NULL){
		if(strcmp(aux->name,called)==0){
			table_element* local = aux->locals;
			while(local!=NULL){
				param+=local->param;
				local=local->next;
			}
			return param;
		}
		aux=aux->next;
	}
	return param;
}

//devolve o tipo de um parametro especificado pelo numero da sua posicao num determinado metodo
char* getParambyPos(prog_env* prog,char*called,int pos)
{
    
	environment_list* aux;
	aux = prog->methods;
	int param=-1;
	//verifica variaveis locais do metodo em questao
	while(aux!=NULL){
		if(strcmp(aux->name,called)==0){
			table_element* local = aux->locals;
			while(local!=NULL){
				param+=local->param;
				if(pos == param){
					return local->type;
				}
				local=local->next;
			}
		}
		aux=aux->next;
	}
	return NULL;
}


