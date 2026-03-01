.global _start
_start:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	subq $8, %rsp
	pushq $7
	popq %rax
	movq %rax, -8(%rbp)
	pushq $203
	popq %rax
	movq %rax, -16(%rbp)
	pushq -8(%rbp)
	pushq -16(%rbp)
	pushq -8(%rbp)
	popq %rbx
	popq %rax
	mov %rax, %rdx
	cqo
	idiv %rbx
	pushq %rax
	popq %rbx
	popq %rax
	add %rbx, %rax
	pushq %rax
	movq %rax, %rdi
	movq $60, %rax
	syscall
