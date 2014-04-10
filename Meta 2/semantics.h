#include "structures.h"
#include "symbol_table.h"

prog_env *check_program(is_node* node);
void check_class(is_node *node, prog_env *prog);
void check_type(is_node *node);
