	.section	__TEXT,__text,regular,pure_instructions
	.globl	_funcaoQueDevolveBool
	.align	4, 0x90
_funcaoQueDevolveBool:                  ## @funcaoQueDevolveBool
	.cfi_startproc
## BB#0:
	xorl	%eax, %eax
	ret
	.cfi_endproc

	.globl	_funcaoSemArgumentos
	.align	4, 0x90
_funcaoSemArgumentos:                   ## @funcaoSemArgumentos
	.cfi_startproc
## BB#0:
	xorl	%eax, %eax
	ret
	.cfi_endproc

	.globl	_func
	.align	4, 0x90
_func:                                  ## @func
	.cfi_startproc
## BB#0:
	xorl	%eax, %eax
	ret
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rax
Ltmp1:
	.cfi_def_cfa_offset 16
	movl	$10, _global_int(%rip)
	movl	$1, _sadas(%rip)
	movl	_global_int(%rip), %esi
	leaq	L_str(%rip), %rdi
	xorl	%eax, %eax
	callq	_printf
	xorl	%eax, %eax
	popq	%rdx
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_str:                                  ## @str
	.asciz	"%d\n"

L_.str2:                                ## @.str2
	.asciz	"%s\n"

L_.str:                                 ## @.str
	.asciz	"true"

	.section	__DATA,__data
	.globl	_.true                  ## @.true
	.align	3
_.true:
	.quad	L_.str

	.section	__TEXT,__cstring,cstring_literals
L_.str1:                                ## @.str1
	.asciz	"false"

	.section	__DATA,__data
	.globl	_.false                 ## @.false
	.align	3
_.false:
	.quad	L_.str1

	.globl	_global_int             ## @global_int
.zerofill __DATA,__common,_global_int,4,2
	.globl	_asdsa                  ## @asdsa
.zerofill __DATA,__common,_asdsa,4,2
	.globl	_sadas                  ## @sadas
.zerofill __DATA,__common,_sadas,4,2
	.globl	_sadsa                  ## @sadsa
.zerofill __DATA,__common,_sadsa,4,2
	.globl	_global_boolean         ## @global_boolean
.zerofill __DATA,__common,_global_boolean,1,0
	.globl	_x                      ## @x
.zerofill __DATA,__common,_x,4,2

.subsections_via_symbols
