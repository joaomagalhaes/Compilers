#include "structures.h"
#include "symbol_table.h"

// verificao do no Program
prog_env *check_program(is_node* node);
void check_class(is_node *node, prog_env *prog);

// verificacao do no MethodDecl
void check_methodDecl(prog_env* prog, is_node* node);

// inserir um elemento na tabela global
void insert_global_table(prog_env* prog, char* id, char* type);

// inserir um novo metodo
void insert_methods_table(prog_env* prog, char* id, char* type);

// inserir um elemento num metodo
void insert_method_elements(prog_env* prog, char* method_name, char* type, char* name, int par);

void check_methodParams(prog_env* prog, char* name, is_node* type);

void check_methodBody(prog_env* prog, char* name, is_node* node);
