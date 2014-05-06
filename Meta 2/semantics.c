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
            check_defined(temp->next->name, id);
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
                    check_defined(method_element->name, name);
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
            //printf("estou no metodo de nome %s\n", method_name);
            
            while(aux2 != NULL)
            {
                if(aux2->type == MethodBody)
                    rec_semantic_verification(mySemantic, method_name, aux2->child);
                
                aux2 = aux2->next;
            }
        }
        aux = aux->next;
    }
}

// Funcao recursiva que recebe um no e verifica os seus irmaos
// Dependendo do tipo de no, faz as verificacoes semanticas necessarias
void rec_semantic_verification(prog_env* prog, char* name, is_node* node)
{
    int debug = 0;
    is_node* aux;
    char* type_aux;
    
    while(node != NULL)
    {
        if(node->type == CompoundStat)
        {
            if(debug == 1) printf("No CompoundStat Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == IfElse)
        {
            if(debug == 1) printf("No IfElse Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == Print)
        {
            if(debug == 1) printf("No Print Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Return)
        {
            if(debug == 1) printf("No Return Encontrado\n");
            if(node->child != NULL)
                rec_semantic_verification(prog, name, node->child);

        } else if(node->type == Store)
        {
            if(debug == 1) printf("No Store Encontrado\n");
            check_symbol_existence(node->child, prog, name, 0);
            //rec_expr(prog, name, node->child->next);
            //check_store(node->child, prog, name);
            //check_incompatible_assignment(node->child, prog, name);

        } else if(node->type == StoreArray)
        {
            if(debug == 1) printf("No StoreArray Encontrado\n");
            check_symbol_existence(node->child, prog, name, 0);
            //check_incompatible_assignment_array(node->child, prog, name);
            rec_semantic_verification(prog, name, node->child->next);

        } else if(node->type == While)
        {
            if(debug == 1) printf("No While Encontrado\n");
            rec_semantic_verification(prog, name, node->child);

        } else if(node->type == Call)
        {
            if(debug == 1) printf("No Call Encontrado\n");
            check_symbol_existence(node->child, prog, name, 1);
            check_arguments(node, prog, name);
            rec_semantic_verification(prog, name, node->child->next);
        
        } else if(node->type == Or)
        {
            if(debug == 1) printf("No Or Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == And)
        {
            if(debug == 1) printf("No And Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Eq)
        {
            if(debug == 1) printf("No Eq Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Neq)
        {
            if(debug == 1) printf("No Neq Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Lt)
        {
            if(debug == 1) printf("No Lt Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
           
        } else if(node->type == Gt)
        {
            if(debug == 1) printf("No Gt Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == Leq)
        {
            if(debug == 1) printf("No Leq Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Geq)
        {
            if(debug == 1) printf("No Geq Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Add)
        {
            if(debug == 1) printf("No Add Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Sub)
        {
            if(debug == 1) printf("No Sub Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Mul)
        {
            if(debug == 1) printf("No Mul Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Div)
        {
            if(debug == 1) printf("No Div Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Mod)
        {
            if(debug == 1) printf("No Mod Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == Minus)
        {
            if(debug == 1) printf("No Minus Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == Plus)
        {
            if(debug == 1) printf("No Plus Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
         
        } else if(node->type == Length)
        {
            if(debug == 1) printf("No Length Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == LoadArray)
        {
            if(debug == 1) printf("No LoadArray Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == NewInt)
        {
            if(debug == 1) printf("No NewInt Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == NewBool)
        {
            if(debug == 1) printf("No NewBool Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
            
        } else if(node->type == ParseArgs)
        {
            if(debug == 1) printf("No ParseArgs Encontrado\n");
            rec_semantic_verification(prog, name, node->child);
        
        } else if(node->type == Id)
        {
            if(debug == 1) printf("No Id encontrado\n");
            check_symbol_existence(node, prog, name, 0);
            //check_call(node->child, prog, name);
        }
        
        node = node->next;
    }
}
/*
rec_expr(prog, name, node->child->next)
{
    
}
*/

// (1) Cannot find symbol %s
// Recebe um no (id), e um tipo (0 - variavel, 1 - metodo)
// Procura a variavel ou metodo nas tabelas de simbolo para verificar se existe
void check_symbol_existence(is_node* node, prog_env* prog, char* method_name, int type)
{
    int found = 0, debug = 0;
    
    table_element* temp;
    temp = prog->global;
    
    environment_list* aux;
    aux = prog->methods;
    
    if(type == 0) // procurar variavel
    {
        if(debug) printf("Verificar se a variavel %s existe\n", node->id);
        
        // verifica nas variveis globais
        while(temp != NULL)
        {
            if(strcmp(temp->name, node->id) == 0 && strcmp(temp->type, "method") != 0)
            {
                if(debug) printf("variavel encontrada na tabela de simbolos global\n\n");
                found = 1;
            }
            temp = temp->next;
        }
        
        // verifica nas variaveis locais do metodo em q esta
        while(aux != NULL)
        {
            if(strcmp(aux->name, method_name) == 0)
            {
                table_element* local = aux->locals;
                while(local != NULL)
                {
                    if(strcmp(local->name, node->id) == 0)
                    {
                        if(debug) printf("variavel encontrada na tabela de simbolos do seu metodo\n\n");
                        found = 1;
                    }
                    local = local->next;
                }
            }
            aux = aux->next;
        }
    
    } else // procurar metodo
    {
        //printf("Verificar se o metodo %s existe\n", node->id);
        while(aux != NULL)
        {
            if(strcmp(aux->name, node->id) == 0)
            {
                //printf("metodo encontrado\n\n");
                found = 1;
            }
            aux = aux->next;
        }
    }
    
    if(found == 0)
    {
        printf("Cannot find symbol %s\n", node->id);
        exit(0);
    }
}


// (2) Incompatible type of argument %d in call to method %s (got %s, required %s)
// Recebe um no (Call) e verifica se os argumentos passados estao correctos
void check_arguments(is_node* call, prog_env* prog, char* method_name)
{
    int debug = 0;
    
    if(debug) printf("verificar se os argumentos passados na funcao, estao correctos\n");
    
	table_element* temp;
	temp = prog->global;
    
	environment_list* aux;
	aux = prog->methods;
	
    int ver = 0;
	int nparams = -1;
	char* methodCalled;
	
    if(debug) printf("verificar se o metodo chamado existe\n");
	
    while(temp != NULL)
    {
		if(strcmp(temp->name, call->child->id) == 0)
        {
			ver = 1;
			methodCalled = temp->name;
            if(debug) printf("metodo existe, chama-se %s\n", methodCalled);
		}
		temp = temp->next;
	}
	
	if(ver == 0)
    {
		printf("Cannot find symbol %s\n", call->child->id);
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
	is_node* params = call->child->next;
    
	while(params != NULL)
    {
		nparams++;
		localtemp = localtemp->next;
		
        if(localtemp != NULL)
        {
			if (localtemp->param == 1)
            {
				char* paramtype = getType(params->id, prog, method_name);
                
				//variavel nao declarada
				if(paramtype ==	NULL)
                {
					printf("Cannot find symbol %s\n", params->id);
					exit(0);
				}
                
				//tipos incompativeis
				if(strcmp(localtemp->type, paramtype) != 0)
                {
					printf("Incompatible type of argument %d in call to method %s (got %s, required %s)\n",nparams,methodCalled,paramtype,localtemp->type);
					exit(0);
				}
                
			}else
            {
				//parametros a mais escritos
				printf("Incompatible type of argument %d in call to method %s (got %s, required void)\n", nparams, methodCalled, getType(params->id, prog, method_name));
				exit(0);
			}
		}else{
			//parametros a mais escritos
			printf("Incompatible type of argument %d in call to method %s (got %s, required void)\n",nparams,methodCalled, getType(params->id, prog, method_name));
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

// (3) Incompatible type in assignment to %s (got %s, required %s)
// recebe um no Store, verifica se os tipos sao compativeis
void check_incompatible_assignment(is_node *store, prog_env* prog, char* method_name)
{
    char* type1 = getType(store->id, prog, method_name);
    char* type2 = typeCast(sem_type[store->next->type]);
    
    printf("No Store detetado! Verificar Compatabilidade entre:\n- variavel %s do tipo %s\n- objeto com o tipo %s\n", store->id, type1, type2);

    if(strcmp(type1, type2) != 0)
    {
        printf("Incompatible type in assigment to %s (got %s, required %s)\n", store->id, type2, type1);
        exit(0);
    }
}

// (4) Incompatible type in assignment to %s[] (got %s, required %s)
// recebe um no StoreArray, verifica se os tipos sao compativeis
void check_incompatible_assignment_array(is_node *storeArray, prog_env* prog, char* method_name)
{
    char* type1 = getType(storeArray->id, prog, method_name);
    char* type2 = typeCast(sem_type[storeArray->next->next->type]);
    
    if(strcmp(type1, "int[]") == 0)
        type1 = "int";
    else if(strcmp(type1, "boolean[]") == 0)
        type1 = "boolean";

    printf("No StoreArray detetado! Verificar Compatabilidade entre:\n- variavel %s do tipo %s\n- objeto com o tipo %s\n", storeArray->id, type1, type2);
    
    if(strcmp(type1, type2) != 0)
    {
        printf("Incompatible type in assigment to %s[] (got %s, required %s)\n", storeArray->id, type2, type1);
        exit(0);
    }
}

// (10) Symbol %s already defined
void check_defined(char* name, char* nameNew)
{
	if(strcmp(name,nameNew) == 0)
    {
		printf ("Symbol %s already defined\n", name);
		exit(0);
	}
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

// recebe nome de variavel e nome de metodo em que pode estar
// devolve o tipo da variavel caso exista
// devolve NULL caso nao exista
char* getType(char* nameP, prog_env* prog, char* methodName)
{
	table_element* temp;
	temp = prog->global;
    
	environment_list* aux;
	aux = prog->methods;
    
    
	// verifica variaveis globais
	while(temp != NULL)
    {
		if(strcmp(temp->name, nameP) == 0 && strcmp(temp->type, "method") != 0)
			return temp->type;
		temp = temp->next;
	}
    
	// verifica variaveis locais do metodo em questao
	while(aux != NULL)
    {
		if(strcmp(aux->name, methodName) == 0)
        {
			table_element* local = aux->locals;
			while(local != NULL)
            {
				if(strcmp(local->name, nameP) == 0)
					return local->type;
				local = local->next;
			}
			return NULL;
		}
		aux = aux->next;
	}
	return NULL;
}

// cast entre tipos na AST e tipos da tabela de simbolo
char* typeCast(char* type)
{
    if(strcmp(type, "IntLit") == 0)
        return "int";
    else if(strcmp(type, "BoolLit") == 0)
        return "boolean";
    else if(strcmp(type, "NewInt") == 0)
        return "int";
    else if(strcmp(type, "NewBool") == 0)
        return "boolean";
    else if(strcmp(type, "Int") == 0)
        return "int";
    else if(strcmp(type, "Bool") == 0)
        return "boolean";
    else if(strcmp(type, "Void") == 0)
        return "void";
    else if(strcmp(type, "IntArray") == 0)
        return "int[]";
    else if(strcmp(type, "BoolArray") == 0)
        return "boolean[]";
    else if(strcmp(type, "StringArray") == 0)
        return "String[]";
    else
    {
        printf("erro na func typeCast\n");
        return NULL;
    }
}





