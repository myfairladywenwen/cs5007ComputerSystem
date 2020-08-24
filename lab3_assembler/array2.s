	.file	"array2.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$1600, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	assert@PLT
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	movq	-8(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movl	$1, (%rax)
	movq	-8(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movl	$2, (%rax)
	movq	-8(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movl	$3, (%rax)
	movq	-8(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movl	$4, (%rax)
	movq	-8(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movl	$5, (%rax)
	movq	-8(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movl	$6, (%rax)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
