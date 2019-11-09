SECTION .bss
	dest resb 5
	destlen equ ($-dest)
	
	char resb 1
SECTION .data
	src db 0,1,2,3,4
	srclen equ ($-src)
SECTION .text
	global _start
putchar:
	mov rax, 4
	mov rbx, 1
	mov rdx, 1
	int 0x80
	ret

_start:
	mov r8, src
	mov r9, dest

	mov rdi, r8
	add byte[rdi], 48
	mov rcx, rdi
	call putchar
	mov byte[char], 10
	mov rcx, char
	call putchar



exit:
	mov rax, 1
	mov rbx, 1
	int 0x80
