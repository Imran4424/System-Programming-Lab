	.file	"mytest.c"
	.section	.rodata
.LC0:
	.string	"add is : %d\n"
.LC1:
	.string	"substract is : %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$3, %esi
	movl	$5, %edi
	call	int_add
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$3, %esi
	movl	$5, %edi
	call	int_sub
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.2 20140120 (Red Hat 4.8.2-16)"
	.section	.note.GNU-stack,"",@progbits
