%include "MemFuncs.asm"

section .bss
	buf resq 5
	buflen equ ($-buf)/8
section .data
	dat dq 0,1,2,3,4
	datlen equ ($-dat)/8
section .text
	global _start

putchar:
	mov rax, 4
	mov rbx, 1
	mov rdx, 1
	int 80h
	ret

_start:
	mov	r8, dat
	mov	r9, datlen

loop1:
	mov rdi, r8
	add QWORD [rdi], 48
	mov rcx, rdi
	call putchar
	add r8, 8
	dec r9
	jnz loop1
	
	mov rax, dat
	mov rbx, 2
	mov rcx, 8
	mov rdx, buf
	call asm_memcpy
	mov r8, buf
	mov r9, buflen
loop2:
	mov rdi, r8
	add QWORD [rdi], 48
	mov rcx, rdi
	call putchar
	add r8, 8
	dec r9
	jnz loop2

exit:
	mov	rbx, 0
	mov	rax, 1
	int 80H
