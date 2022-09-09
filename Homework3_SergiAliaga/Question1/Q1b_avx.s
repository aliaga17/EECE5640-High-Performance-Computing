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
	vmovss	%xmm0, -36(%rbp)
	vcvtss2sd	-36(%rbp), %xmm0, %xmm0
	vmovsd	.LC0(%rip), %xmm1
	vmulsd	%xmm1, %xmm0, %xmm0
	vmovsd	.LC1(%rip), %xmm1
	vdivsd	%xmm1, %xmm0, %xmm0
	vcvtsd2ss	%xmm0, %xmm0, %xmm0
	vmovss	%xmm0, -20(%rbp)
	vmovss	-20(%rbp), %xmm0
	vmovss	%xmm0, -4(%rbp)
	vmovss	.LC2(%rip), %xmm0
	vmovss	%xmm0, -8(%rbp)
	vmovss	-20(%rbp), %xmm0
	vmovss	%xmm0, -12(%rbp)
	movl	$1, -16(%rbp)
	jmp	.L2
.L3:
	vmovss	-12(%rbp), %xmm0
	vmulss	-20(%rbp), %xmm0, %xmm0
	vmovss	-20(%rbp), %xmm1
	vmulss	%xmm0, %xmm1, %xmm0
	vmovss	%xmm0, -12(%rbp)
	movl	-16(%rbp), %eax
	addl	%eax, %eax
	vcvtsi2ssl	%eax, %xmm0, %xmm0
	vmulss	-8(%rbp), %xmm0, %xmm1
	movl	-16(%rbp), %eax
	addl	%eax, %eax
	incl	%eax
	vcvtsi2ssl	%eax, %xmm0, %xmm0
	vmulss	%xmm0, %xmm1, %xmm0
	vmovss	%xmm0, -8(%rbp)
	movl	-16(%rbp), %eax
	cltd
	shrl	$31, %edx
	addl	%edx, %eax
	andl	$1, %eax
	subl	%edx, %eax
	leal	(%rax,%rax), %edx
	movl	$1, %eax
	subl	%edx, %eax
	vcvtsi2ssl	%eax, %xmm0, %xmm0
	vmulss	-12(%rbp), %xmm0, %xmm0
	vdivss	-8(%rbp), %xmm0, %xmm0
	vmovss	-4(%rbp), %xmm1
	vaddss	%xmm0, %xmm1, %xmm0
	vmovss	%xmm0, -4(%rbp)
	incl	-16(%rbp)
.L2:
	cmpl	$9999999, -16(%rbp)
	jle	.L3
	vmovss	-4(%rbp), %xmm0
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
	vxorpd	%xmm0, %xmm0, %xmm0
	vmovsd	%xmm0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L6
.L7:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	vmovsd	(%rax), %xmm1
	vcvtsi2sdl	-28(%rbp), %xmm0, %xmm0
	vdivsd	%xmm0, %xmm1, %xmm0
	vmovsd	-8(%rbp), %xmm1
	vaddsd	%xmm0, %xmm1, %xmm0
	vmovsd	%xmm0, -8(%rbp)
	incl	-12(%rbp)
.L6:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L7
	vmovsd	-8(%rbp), %xmm0
	vmovq	%xmm0, %rax
	vmovq	%rax, %xmm0
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
	vmovss	angles(,%rax,4), %xmm0
	vcvtss2sd	%xmm0, %xmm0, %xmm2
	vmovq	%xmm2, %rax
	vmovq	%rax, %xmm0
	movl	$.LC5, %edi
	movl	$1, %eax
	call	printf
	incl	-4(%rbp)
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
	vmovd	%eax, %xmm0
	call	sin_float
	vmovd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	leaq	-64(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday
	movq	-56(%rbp), %rax
	movq	-40(%rbp), %rdx
	subq	%rdx, %rax
	vcvtsi2sdq	%rax, %xmm0, %xmm0
	vmovsd	.LC7(%rip), %xmm1
	vdivsd	%xmm1, %xmm0, %xmm1
	movq	-64(%rbp), %rax
	movq	-48(%rbp), %rdx
	subq	%rdx, %rax
	vcvtsi2sdq	%rax, %xmm0, %xmm0
	vaddsd	%xmm0, %xmm1, %xmm0
	movl	-8(%rbp), %eax
	cltq
	vmovsd	%xmm0, time_float(,%rax,8)
	vcvtss2sd	-20(%rbp), %xmm0, %xmm0
	movl	-8(%rbp), %eax
	cltq
	vmovss	angles(,%rax,4), %xmm1
	vcvtss2sd	%xmm1, %xmm1, %xmm3
	vmovq	%xmm3, %rax
	vmovsd	%xmm0, %xmm0, %xmm1
	vmovq	%rax, %xmm0
	movl	$.LC8, %edi
	movl	$2, %eax
	call	printf
	incl	-8(%rbp)
.L12:
	cmpl	$3, -8(%rbp)
	jle	.L13
	movl	$4, %esi
	movl	$time_float, %edi
	call	average
	vmovq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	vmovq	%rax, %xmm0
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
