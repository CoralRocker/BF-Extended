SECTION .bss

SECTION .data
	array 		db 1, 2, 3, 4, 5
	arraylen 	equ $-array

SECTION .text
	global	_start

_start:
	mov r8, arraylen ; Store Array Length in Register
	mov r9, array	; Store array pointer into register. Allows for pointer arithmetic
_loop:
	add BYTE [r9], 48 ; ASCII-ify the current array loc.
	mov rax, 4	; SYS_WRITE
	mov rbx, 1	; STDOUT
	mov rcx, r9	; Load array into rcx	
	mov rdx, 1	; Write 1 byte
	int 0x80	; SYSCALL	
	inc r9		; Increment Array Pointer
	dec r8		; Decrement loop counter
	jnz _loop	; Loop if loop counter is not 0. IE, don't jump if zero

newline:
	mov rax, 4
	mov rbx, 1
	mov BYTE [array], 10
	mov rcx, array
	mov rdx, 1
	int 0x80

exit:
	mov	rbx,	0		; Error code 0
	mov	rax,	1		; Syscall 1 (exit)
	int	80h
