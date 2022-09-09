	.file	"Q1b.c"
	.text
	.globl	angles
	.data
	.align 16
	.type	angles, @object
	.size	angles, 16
angles:
	.long	1092616192
	.long	1101004800
	.long	1106247680
	.long	1109393408
	.globl	time_float
	.bss
	.align 32
	.type	time_float, @object
	.size	time_float, 32
time_float:
	.zero	32
	.text
	.globl	sin_float
	.type	sin_float, @function
sin_float:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -36(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-36(%rbp), %xmm1
	movsd	.LC0(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	.LC1(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	movl	$1, -16(%rbp)
	jmp	.L2
.L3:
	movss	-12(%rbp), %xmm0
	mulss	-20(%rbp), %xmm0
	movss	-20(%rbp), %xmm1
	mulss	%xmm1, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	-16(%rbp), %eax
	addl	%eax, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movaps	%xmm0, %xmm1
	mulss	-8(%rbp), %xmm1
	movl	-16(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movl	-16(%rbp), %eax
	cltd
	shrl	$31, %edx
	addl	%edx, %eax
	andl	$1, %eax
	subl	%edx, %eax
	leal	(%rax,%rax), %edx
	movl	$1, %eax
	subl	%edx, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	mulss	-12(%rbp), %xmm0
	divss	-8(%rbp), %xmm0
	movss	-4(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	addl	$1, -16(%rbp)
.L2:
	cmpl	$9999999, -16(%rbp)
	jle	.L3
	movss	-4(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	sin_float, .-sin_float
	.globl	average
	.type	average, @function
average:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L6
.L7:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-28(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
.L6:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L7
	movsd	-8(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	average, .-average
	.section	.rodata
.LC4:
	.string	"Computing sin(x) for x="
.LC5:
	.string	"%f, "
.LC6:
	.string	"degrees\n"
.LC8:
	.string	"FLOAT Sin(%.1f) = %f\n"
	.align 8
.LC9:
	.string	"Average computing time FLOAT: %f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movl	-4(%rbp), %eax
	cltq
	movss	angles(,%rax,4), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	movl	$.LC5, %edi
	movl	$1, %eax
	call	printf
	addl	$1, -4(%rbp)
.L10:
	cmpl	$3, -4(%rbp)
	jle	.L11
	movl	$.LC6, %edi
	call	puts
	movl	$0, -8(%rbp)
	jmp	.L12
.L13:
	leaq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday
	movl	-8(%rbp), %eax
	cltq
	movl	angles(,%rax,4), %eax
	movd	%eax, %xmm0
	call	sin_float
	movd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	leaq	-64(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday
	movq	-56(%rbp), %rax
	movq	-40(%rbp), %rdx
	subq	%rdx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC7(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movq	-64(%rbp), %rax
	movq	-48(%rbp), %rdx
	subq	%rdx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	addsd	%xmm1, %xmm0
	movl	-8(%rbp), %eax
	cltq
	movsd	%xmm0, time_float(,%rax,8)
	pxor	%xmm0, %xmm0
	cvtss2sd	-20(%rbp), %xmm0
	movl	-8(%rbp), %eax
	cltq
	movss	angles(,%rax,4), %xmm1
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm1, %xmm4
	movq	%xmm4, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	movl	$.LC8, %edi
	movl	$2, %eax
	call	printf
	addl	$1, -8(%rbp)
.L12:
	cmpl	$3, -8(%rbp)
	jle	.L13
	movl	$4, %esi
	movl	$time_float, %edi
	call	average
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	movl	$.LC9, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	1413754136
	.long	1074340347
	.align 8
.LC1:
	.long	0
	.long	1080459264
	.align 4
.LC2:
	.long	1065353216
	.align 8
.LC7:
	.long	0
	.long	1093567616
	.ident	"GCC: (GNU) 10.1.0"
	.section	.note.GNU-stack,"",@progbits
