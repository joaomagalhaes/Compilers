#include "structures.h"

// Start
is_node *insertProgram(is_node *progbody);

// Program
is_node *insertProgAux(is_node *id, is_node *fieldsmethods);

// FieldMethodDecl

// FieldDecl


// MethodDecl
is_node *insertMethodDecl(is_node *type, is_node *id, is_node *params, is_node *varDecl, is_node *stats);

// MethodVarDecl

// FormalParams
is_node *insertFormalParams1(is_node *type, is_node *id);
is_node *insertFormalParams2(is_node *type, is_node *id, is_node *moreNodes);

// CommaTypeID
is_node *insertFPRepetition(is_node *type, is_node *id, is_node *extra_node);

// VarDecl

// CommaID
is_node *insertVarDecl(is_node *type, is_node *id, is_node *moreIDS);

// Type

// Statement
is_node *insertST_compoundstat(is_node *stat);
is_node *insertST_if_else(is_node *expr, is_node *stat, is_node *stat2);
is_node *insertST_while_expr_stat(is_node *expr, is_node *stat);
is_node *insertST_print_expr_sem(is_node *expr);
is_node *insertST_id_expr_assign_expr(is_node *id, is_node *expr1, is_node *expr2);
is_node *insertST_id_assign_exp_sem(is_node *id, is_node *exp);
is_node *insertST_ret_exp_sem(is_node *expr);
is_node *insertST_ret_null();

// StatRep

// Expr
is_node *insert_expr_ope_expr(is_node *expr1, char* oper, is_node *expr2);
is_node *insert_expr_squares_expr(is_node *expr1, is_node *expr2);
is_node *insert_length(is_node *expr);
is_node *insert_Oper_Exp(char* oper, is_node *expr);
is_node *insert_new_exp(node_type type, is_node *expr);
is_node *insert_ParseInt(is_node *id, is_node *expr);
is_node *insert_id_args(is_node *id, is_node *args);

// Auxs
is_node *insert_ID(char* str);
is_node *insert_INTLIT(char* str);
is_node *insert_BOOLLIT(char* str);
is_node *insertType(node_type type);
is_node *insertRepetition(is_node *x, is_node *y);
is_node *insertStatRepetition(is_node *stat, is_node *stat2);
is_node *nullNode();

