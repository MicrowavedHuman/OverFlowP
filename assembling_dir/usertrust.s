.global _start
_start:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	pushq $4
	popq %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	pushq -8(%rbp)
	pushq $3
	popq %rbx
	popq %rax
	cmp %rbx, %rax
	setg %al
	movzbq %al, %rax
	pushq %rax
	popq %rax
	cmpq $0, %rax
	je _and_false_1
	pushq -8(%rbp)
	pushq $13
	popq %rbx
	popq %rax
	cmp %rbx, %rax
	setg %al
	movzbq %al, %rax
	pushq %rax
	popq %rax
	jmp _and_end_2
_and_false_1:
	movq $0, %rax
_and_end_2:
	pushq %rax
	popq %rax
	cmpq $0, %rax
	je else_0
	pushq -8(%rbp)
	pushq -8(%rbp)
	pushq $1
	popq %rbx
	popq %rax
	add %rbx, %rax
	pushq %rax
	popq %rbx
	popq %rax
	imul %rbx, %rax
	pushq %rax
	popq %rdi
	movq $60, %rax
	syscall
	jmp end_if_0
else_0:
	pushq $13
	popq %rdi
	movq $60, %rax
	syscall
end_if_0:
