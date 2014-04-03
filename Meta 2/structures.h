#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum
{
	Program, 
	VarDecl, 
	MethodDecl, MethodParams, MethodBody, ParamDeclaration, 
	CompoundStat, IfElse, Print, Return, Store, StoreArray, While,
	Or, And, Eq, Neq, Lt, Gt, Leq, Geq, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Length, LoadArray, Call, ParseArgs,
	Int, Bool, IntArray, BoolArray, StringArray, Void, Id, IntLit, BoolLit,
	Null
}node_type;

typedef struct _a3
{
	char* id;
 	node_type type;
 	struct _a3 *child;
 	struct _a3 *next;
}is_node;

#endif
