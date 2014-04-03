#include "structures.h"

// Start

// Program
is_node *insertProgram(is_node *id, is_node *fieldsmethods);

// FieldMethodDecl

// FieldDecl


// MethodDecl
is_node *insertMethodDecl(is_node *type, is_node *id, is_node *params, is_node *varDecl, is_node *stats);

// MethodVarDecl

// FormalParams
is_node *insertFormalParams1(is_node *type, is_node *id);
is_node *insertFormalParams2(is_node *type, is_node *id, is_node *moreNodes);

// CommaTypeID
is_node *insertFPRepetition(is_node *type, is_node *id);

// VarDecl

// CommaID
is_node *insertVarDecl(is_node *type, is_node *id, is_node *moreIDS);

// Type

// Statement
is_node *insertST_if_else(is_node *expr, is_node *stat, is_node *stat2);
is_node *insertST_ret_exp_sem(is_node *expr);
 
// StatRep

// Exp

// Auxs
is_node *insert_ID(char* str);
is_node *insert_INTLIT(char* str);
is_node *insertType(node_type type);
is_node *insertRepetition(is_node *x, is_node *y);


