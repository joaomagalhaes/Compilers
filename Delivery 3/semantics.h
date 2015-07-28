#include "structures.h"
#include "symbol_table.h"

// Recebe arvore sintaxe abstracta (no Program)
// Devolve tabela de simbolos
prog_env *check_program(is_node* node);


// Recebe filhos do no 'Program'
// Se Id adicionar nome da classe na tabela de simbolos global
// Se VarDecl adiciona variavel na tabela de simbolos global
// Se MethodDecl adiciona metodo na tabela de simbolos global e cria tabela simbolos do metodo
void check_class(is_node *node, prog_env *prog);


// Recebe filhos do no 'MethodDecl'
// Adiciona o elemento return <tipo> na tabela de simbolo do metodo correspondente
// Chama as funcoes de verificacoes dos no filhos (MethodParams e MethodBody)
void check_methodDecl(prog_env* prog, is_node* node);


// Recebe filhos do no 'MethodBody'
// Se VarDecl adiciona a variavel na tabela de simbolos do metodo correspondente
void check_methodBody(prog_env* prog, char* name, is_node* node);


// Recebe filhos do no 'MethodParams'
// Adiciona os parametros na tabela de simbolos do metodo correspondente
void check_methodParams(prog_env* prog, char* name, is_node* node);


// Funcao Auxiliar - insercao na tabela de simbolos global
// Verificao do erro semantico 'Symbol already defined'
void insert_global_table(prog_env* prog, char* id, char* type);


// Funcao Auxiliar - insercao de nova tabela de simbolos de metodo
void insert_methods_table(prog_env* prog, char* id, char* type);


// Funcao Auxiliar - insercao de elemento na tabela de simbolos do metodo correspondente
// Verificao do erro semantico 'Symbol already defined'
void insert_method_elements(prog_env* prog, char* method_name, char* type, char* name, int par);


// Recebe arvore sintaxe abstracta e tabela de simbolos
// Procura nos MethodBody
void check_semantic(is_node* myProgram, prog_env* mySemantic);


// Funcao recursiva que recebe um no e verifica os seus irmaos
// Dependendo do tipo de no, faz as verificacoes semanticas necessarias
void semantic_statements(prog_env* prog, char* name, is_node* node);


char* expr_recursive(prog_env* prog, char* method_name, is_node* expr);


// (1) Cannot find symbol %s
// Recebe um no (id), e um tipo (0 - variavel, 1 - metodo)
// Procura a variavel ou metodo nas tabelas de simbolo para verificar se existe
void check_symbol_existence(is_node* node, prog_env* prog, char* method_name, int type);


// (2) Incompatible type of argument %d in call to method %s (got %s, required %s)
// Recebe um no (Call) e verifica se os argumentos passados estao correctos
void check_arguments(is_node* call, prog_env* prog, char* name);


//(7) Invalid literal
void check_literal(char* lit);


// (10) Symbol already defined
void check_defined(char* name, char* nameNew);


// recebe nome de variavel e nome de metodo em que pode estar
// devolve o tipo da variavel caso exista
// devolve NULL caso nao exista
char* getType(char* nameP,prog_env* prog,char*methodName);


// recebe o nome de um metodo, devolve o que ele retorna em string
char* method_return(prog_env* prog, char* method_name);

// recebe um metodo e o indice do argumento e devolve o tipo desse argumento
char* getArgumentType(prog_env* prog, char* method_called, int index);





