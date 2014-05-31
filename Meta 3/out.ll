
declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*) nounwind readonly
@str = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@.str2 = private unnamed_addr constant [4 x i8] c"%s\0A\00"
@.str = private unnamed_addr constant [5 x i8] c"true\00"
@.true = global i8* getelementptr inbounds ([5 x i8]* @.str, i32 0, i32 0)
@.str1 = private unnamed_addr constant [6 x i8] c"false\00"
@.false = global i8* getelementptr inbounds ([6 x i8]* @.str1, i32 0, i32 0)

@global_int = global i32 0
@asdsa = global i32 0
@sadas = global i32 0
@sadsa = global i32 0
@global_boolean = global i1 0

define i1 @funcaoQueDevolveBool()
{
	%w = alloca i32
	ret i1 0
}

define i32 @funcaoSemArgumentos()
{
	ret i32 0
}

define i32 @func(i32 %a)
{
	ret i32 0
}

define i32 @main(i32 %.argc, i8** %.argv)
{
	store i32 10, i32* @global_int
	store i32 1, i32* @sadas
	%1 = load i32* @global_int
	%2 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @str, i32 0, i32 0), i32 %1)
	ret i32 0
}
@x = global i32 0
