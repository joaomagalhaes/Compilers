#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef enum
{
	Program, 
	VarDecl, 
	MethoDecl, MethodParams, MethodBody, ParamDeclaration, 
	CompoundStat, IfElse, Print, Return, Store, StoreArray, While,
	Or, And, Eq, Neq, Lt, Gt, Leq, Geq, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Length, LoadArray, Call, ParseArgs,
	Int, Bool, IntArray, BoolArray, StringArray, Void, Id, IntLit, BoolLit,
	Null
}node_type;

typedef struct _a3
{
	char* id;
 	node_type type;
 	struct _a3 *child; //filho direto
 	struct _a3 *next; //mesmo nivel
}is_node;

#endif
