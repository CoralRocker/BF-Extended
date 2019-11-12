SECTION .bss
	dest resb 5
	destlen equ ($-dest)
	
	char resb 1
SECTION .data
	src db 40,41,42,43,44
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
	mov r10, srclen
loop1:
	mov rdi, r8
;	add byte[rdi], 48
	mov rcx, rdi
	call putchar
;	mov byte[char], 10
;	mov rcx, char
;	call putchar
	mov [r9], r8
	mov rdi, r9
;	add byte[rdi], 48
	mov rcx, rdi
	call putchar
	mov byte[char], 10
	mov rcx, char
	call putchar
	inc r8
	inc r9
	dec r10
	jnz loop1

	mov r8, src
	mov r9, dest
	mov r10, srclen
loop2:
	mov rdi, r8
;	add byte[rdi], 48
	mov rcx, rdi
	call putchar
	mov rdi, r9
;	add byte[rdi], 48
	mov rcx, rdi
	call putchar
	mov byte[char], 10
	mov rcx, char
	call putchar
	inc r8
	inc r9
	dec r10
	jnz loop2

exit:
	mov rax, 1
	mov rbx, 1
	int 0x80
