global _start

SECTION .bss
	dst resb 1
SECTION .data
	src db 48
SECTION .text
_start:
	mov r8b, src
	mov r9b, dst
	
_loop:
		mov r10b, [r9b]
	mov [dst], r10b

	mov rax, 4
	mov rbx, 1
	mov rcx, dst
	mov rdx, 1
	int 0x80

	mov rax, 1
	mov rbx, 0
	int 0x80
