	.file	"array.c"
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
	subq	$1616, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -1616(%rbp)
	movl	$1, -1612(%rbp)
	movl	$2, -1608(%rbp)
	movl	$3, -1604(%rbp)
	movl	$4, -1600(%rbp)
	movl	$5, -1596(%rbp)
	movl	$9, -1580(%rbp)
	movl	$99, -1220(%rbp)
	movl	$199, -820(%rbp)
	movl	$299, -420(%rbp)
	movl	$398, -24(%rbp)
	movl	$399, -20(%rbp)
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
