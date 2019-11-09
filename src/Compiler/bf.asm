;; %include "MemFuncs.asm"

section .bss
section .data
	array db 1,2,3,4,5
	arraylen equ $-array			; array length * 4 = number of elements
section .text
	global main:
main:
	mov	r8, array					  ; get pointer to array
	mov	r9, arraylen 			   ; edi = number of array elements
.printArr:
	mov	rax, 4
	mov 	rbx, 1
	mov	rdx, 1

	add 	BYTE [r8], 48
	mov 	rcx, r8
	int 	0x80
	sub 	BYTE [r8], 48
	inc 	r8
	dec 	r9
	jnz 	.printArr


.PrintLineFeed:
	sub	rsi, 4
	mov	byte [rsi], 10
	mov	rdx, 1
	mov	rcx, rsi
	mov	rbx, 1
	mov	rax, 4
	int	0x80
	add	rsi, 4						  ; not needed since next call is exit, but learn good techniques.

exit: 
	mov	rbx, 0
	mov	rax, 1
	int 80H
