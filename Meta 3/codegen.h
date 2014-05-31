#include "structures.h"
#include "symbol_table.h"

void generate_code(is_node *node, prog_env* mySemantic);
void gen_statements(char* method_name, is_node* node, prog_env* mySemantic);
char* gen_expression(char* method_name, is_node* expr, prog_env* prog);
char* get_type(char* var_name, prog_env* prog, char* method_name);
char* gen_code_type(char* AST_type);
int verifyGlobal(char* var_name, prog_env* prog, char* method_name);
