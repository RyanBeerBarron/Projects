	.file	"cache.c"
	.text
	.section	.rodata
.LC0:
	.string	"Args counter: %d\n"
	.text
	.globl	parse_cli
	.type	parse_cli, @function
parse_cli:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$1, -32(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	jmp	.L2
.L6:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L3
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movb	$0, (%rax)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	subq	$8, %rdx
	leaq	(%rax,%rdx), %rbx
	movl	$500, %edi
	call	malloc@PLT
	movq	%rax, (%rbx)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	subq	$8, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	-40(%rbp), %rcx
	movl	$50, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	addl	$1, -32(%rbp)
	jmp	.L4
.L5:
	addq	$1, -24(%rbp)
.L4:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L5
	movq	-24(%rbp), %rax
	movq	%rax, -40(%rbp)
.L3:
	addq	$1, -24(%rbp)
.L2:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L6
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	subq	$8, %rdx
	leaq	(%rax,%rdx), %rbx
	movl	$500, %edi
	call	malloc@PLT
	movq	%rax, (%rbx)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	subq	$8, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	-40(%rbp), %rcx
	movl	$50, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	-48(%rbp), %rax
	movl	-32(%rbp), %edx
	movl	%edx, (%rax)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, -28(%rbp)
	jmp	.L7
.L8:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	puts@PLT
	addl	$1, -28(%rbp)
.L7:
	movl	-28(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L8
	movl	$1, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	parse_cli, .-parse_cli
	.globl	ispow2
	.type	ispow2, @function
ispow2:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L11
.L12:
	sall	-4(%rbp)
.L11:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L12
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jne	.L13
	movl	$1, %eax
	jmp	.L14
.L13:
	movl	$0, %eax
.L14:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	ispow2, .-ispow2
	.globl	initialize_cache
	.type	initialize_cache, @function
initialize_cache:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movl	%ecx, -52(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L16
.L19:
	movl	$0, -16(%rbp)
	jmp	.L17
.L18:
	movl	-52(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	$-1, -8(%rbp)
	movl	$0, -4(%rbp)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movq	-12(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	-4(%rbp), %edx
	movl	%edx, 8(%rax)
	addl	$1, -16(%rbp)
.L17:
	movl	-16(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L18
	addl	$1, -20(%rbp)
.L16:
	movl	-20(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jl	.L19
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	initialize_cache, .-initialize_cache
	.section	.rodata
.LC1:
	.string	"-------------"
.LC2:
	.string	"-"
.LC3:
	.string	"| %4x %d "
.LC4:
	.string	"|"
.LC5:
	.string	"-\n"
	.text
	.globl	print_cache
	.type	print_cache, @function
print_cache:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L22
.L29:
	movl	$0, -24(%rbp)
	jmp	.L23
.L24:
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -24(%rbp)
.L23:
	movl	-24(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L24
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movl	$0, -20(%rbp)
	jmp	.L25
.L26:
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movq	(%rax), %rdx
	movq	%rdx, -12(%rbp)
	movl	8(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -20(%rbp)
.L25:
	movl	-20(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L26
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	movl	$0, -16(%rbp)
	jmp	.L27
.L28:
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -16(%rbp)
.L27:
	movl	-16(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L28
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	addl	$1, -28(%rbp)
.L22:
	movl	-28(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jl	.L29
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	print_cache, .-print_cache
	.section	.rodata
	.align 8
.LC6:
	.ascii	"Welcome to the cache simulation.\nPlease enter the attribute"
	.ascii	"s of the cache you want to simulat"
	.string	"e, separated by spaces or commas.\nFirst enter the number of set, n, then the number of directories, k, the number of bytes per cache line, l. They must be powers of 2.\nAlso specify the size of the addresses (8, 16, 32 or 64 bits).\nOr enter \"quit\" to leave."
	.align 8
.LC7:
	.string	"Length of user input: %d\nFirst character: %d\n"
	.align 8
.LC8:
	.string	"Arg counter: %d\nFirst character: %d\n"
.LC9:
	.string	"Temp is: %s\n"
.LC10:
	.string	"Test newline"
.LC11:
	.string	"quit"
.LC12:
	.string	"Test quit"
.LC13:
	.string	"Is integer."
.LC14:
	.string	"Invalid input, try again"
	.align 8
.LC15:
	.string	"The value of temps are: %d %d %d %d\n"
.LC16:
	.string	"Succes"
	.align 8
.LC17:
	.string	"The values of n, k and l are: %d, %d, %d\nAnd the address size is: %d\n"
	.align 8
.LC18:
	.ascii	"If you want to use the default addresses, enter 0.\nIf you w"
	.ascii	"ant to enter addresses at"
	.string	" each step, enter 1.\nIf you want to read addreses from a file enter 2.\nIf you want a trace of the cache simulation add option \"-v\".\nIf you want the trace written in a file, add option \"-f\".\nEnter \"redo\" to change the cache parameters\nEnter \"quit\" to leave."
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$656, %rsp
	movl	%edi, -628(%rbp)
	movq	%rsi, -640(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -612(%rbp)
	leaq	.LC6(%rip), %rdi
	call	puts@PLT
	jmp	.L32
.L59:
	movl	$0, -576(%rbp)
	movl	$0, -608(%rbp)
	movl	$0, -604(%rbp)
	movl	$0, -600(%rbp)
	movl	$0, -596(%rbp)
	jmp	.L33
.L55:
	movl	$0, -592(%rbp)
	movl	$0, -588(%rbp)
	movl	$0, -584(%rbp)
	movl	$0, -580(%rbp)
	movl	$0, -564(%rbp)
	movl	$0, -560(%rbp)
	movl	$0, -528(%rbp)
	movl	$800, %edi
	call	malloc@PLT
	movq	%rax, -520(%rbp)
	movq	stdin(%rip), %rdx
	leaq	-512(%rbp), %rax
	movl	$500, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	testq	%rax, %rax
	je	.L33
	leaq	-512(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -556(%rbp)
	movzbl	-512(%rbp), %eax
	movsbl	%al, %edx
	movl	-556(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpl	$0, -556(%rbp)
	jle	.L33
	movl	-556(%rbp), %eax
	subl	$1, %eax
	cltq
	movb	$0, -512(%rbp,%rax)
	leaq	-528(%rbp), %rdx
	leaq	-512(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parse_cli
	testl	%eax, %eax
	je	.L33
	movzbl	-512(%rbp), %eax
	movsbl	%al, %edx
	movl	-528(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, -572(%rbp)
	jmp	.L34
.L52:
	movq	-520(%rbp), %rax
	movl	-572(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -536(%rbp)
	movq	-536(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-528(%rbp), %eax
	cmpl	$1, %eax
	jne	.L35
	movzbl	-512(%rbp), %eax
	testb	%al, %al
	jne	.L35
	leaq	-512(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L35
	leaq	.LC10(%rip), %rdi
	call	puts@PLT
	jmp	.L36
.L35:
	movl	-528(%rbp), %eax
	cmpl	$1, %eax
	jne	.L37
	movq	-536(%rbp), %rax
	movq	%rax, -552(%rbp)
	jmp	.L38
.L39:
	movq	-552(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	tolower@PLT
	movl	%eax, %edx
	movq	-552(%rbp), %rax
	movb	%dl, (%rax)
	addq	$1, -552(%rbp)
.L38:
	movq	-552(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L39
	movq	-536(%rbp), %rax
	leaq	.LC11(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L36
	leaq	.LC12(%rip), %rdi
	call	puts@PLT
	movl	$0, -612(%rbp)
	movl	$1, -576(%rbp)
	jmp	.L36
.L37:
	movl	-528(%rbp), %eax
	cmpl	$4, %eax
	jne	.L36
	movl	$1, -568(%rbp)
	movq	-536(%rbp), %rax
	movq	%rax, -544(%rbp)
	jmp	.L41
.L44:
	movq	-544(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$44, %al
	jne	.L42
	movq	-544(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L42
	addq	$1, -544(%rbp)
	jmp	.L43
.L42:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rdx
	movq	-544(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$2048, %eax
	testl	%eax, %eax
	jne	.L43
	movl	$0, -568(%rbp)
.L43:
	addq	$1, -544(%rbp)
.L41:
	movq	-544(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L44
	cmpl	$0, -568(%rbp)
	je	.L63
	leaq	.LC13(%rip), %rdi
	call	puts@PLT
	movl	-572(%rbp), %eax
	cmpl	$1, %eax
	je	.L47
	cmpl	$1, %eax
	jg	.L48
	testl	%eax, %eax
	je	.L49
	jmp	.L45
.L48:
	cmpl	$2, %eax
	je	.L50
	cmpl	$3, %eax
	je	.L51
	jmp	.L45
.L49:
	movq	-536(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -592(%rbp)
	jmp	.L45
.L47:
	movq	-536(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -588(%rbp)
	jmp	.L45
.L50:
	movq	-536(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -584(%rbp)
	jmp	.L45
.L51:
	movq	-536(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -580(%rbp)
	jmp	.L45
.L63:
	nop
.L45:
	cmpl	$0, -568(%rbp)
	jne	.L36
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	movl	-528(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -572(%rbp)
.L36:
	addl	$1, -572(%rbp)
.L34:
	movl	-528(%rbp), %eax
	cmpl	%eax, -572(%rbp)
	jl	.L52
	movl	-580(%rbp), %esi
	movl	-584(%rbp), %ecx
	movl	-588(%rbp), %edx
	movl	-592(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC15(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-592(%rbp), %eax
	movl	%eax, %edi
	call	ispow2
	testl	%eax, %eax
	je	.L33
	movl	-588(%rbp), %eax
	movl	%eax, %edi
	call	ispow2
	testl	%eax, %eax
	je	.L33
	movl	-584(%rbp), %eax
	movl	%eax, %edi
	call	ispow2
	testl	%eax, %eax
	je	.L33
	cmpl	$8, -580(%rbp)
	je	.L53
	cmpl	$16, -580(%rbp)
	je	.L53
	cmpl	$32, -580(%rbp)
	je	.L53
	cmpl	$64, -580(%rbp)
	jne	.L33
.L53:
	cvtsi2sd	-580(%rbp), %xmm2
	movsd	%xmm2, -648(%rbp)
	cvtsi2sd	-592(%rbp), %xmm0
	call	log2@PLT
	movsd	%xmm0, -656(%rbp)
	cvtsi2sd	-588(%rbp), %xmm0
	call	log2@PLT
	movapd	%xmm0, %xmm1
	addsd	-656(%rbp), %xmm1
	movsd	%xmm1, -656(%rbp)
	cvtsi2sd	-584(%rbp), %xmm0
	call	log2@PLT
	addsd	-656(%rbp), %xmm0
	movsd	-648(%rbp), %xmm2
	ucomisd	%xmm0, %xmm2
	ja	.L62
	jmp	.L33
.L62:
	leaq	.LC16(%rip), %rdi
	call	puts@PLT
	movl	-592(%rbp), %eax
	movl	%eax, -604(%rbp)
	movl	-588(%rbp), %eax
	movl	%eax, -608(%rbp)
	movl	-584(%rbp), %eax
	movl	%eax, -600(%rbp)
	movl	-580(%rbp), %eax
	movl	%eax, -596(%rbp)
	movl	$1, -576(%rbp)
.L33:
	cmpl	$0, -576(%rbp)
	je	.L55
	cmpl	$0, -576(%rbp)
	je	.L56
	jmp	.L57
.L58:
	movl	-596(%rbp), %esi
	movl	-600(%rbp), %ecx
	movl	-608(%rbp), %edx
	movl	-604(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC18(%rip), %rdi
	call	puts@PLT
	movq	stdin(%rip), %rdx
	leaq	-512(%rbp), %rax
	movl	$500, %esi
	movq	%rax, %rdi
	call	fgets@PLT
.L57:
	cmpl	$0, -612(%rbp)
	jne	.L58
.L56:
	movq	-520(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L32:
	cmpl	$0, -612(%rbp)
	jne	.L59
	movl	$1, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L61
	call	__stack_chk_fail@PLT
.L61:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
