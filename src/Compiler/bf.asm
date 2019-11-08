SECTION .bss
	buffer resq 64

SECTION .text
	global _start

; FUNC DEFS
print_char: ; Must define RCX before calling
	push rax
	push rbx
	push rdx
	
	mov rax, 4
	mov rbx, 1
	mov rdx, 1
	int 0x80

	pop rdx
	pop rbx
	pop rax
	ret	

_start:
	mov r8, buffer

program:
	add BYTE [r8], 6
_loop1:
	inc r8
	add BYTE [r8], 8
	dec r8
	dec BYTE [r8]
	jnz _loop1
	
	inc r8
	mov rcx, r8
	call print_char 
	mov rax, 4
	mov rbx, 1
	mov rcx, 10
	mov rdx, 1
	int 0x80

exit:
	mov rax, 1
	mov rbx, 0
	int 0x80
