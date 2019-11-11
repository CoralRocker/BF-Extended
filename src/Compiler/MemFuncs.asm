SECTION .text

; asm_memcpy(src, num_items, item_size, dst)	
;	rax - src pointer
;	rbx - num_items to take from rax
;	rcx - size of items in bytes
;	rdx - dst pointer
asm_memcpy:
	mov [rdx], rax
	add rax, rcx
	add rdx, rcx
	dec rbx
	jnz asm_memcpy
	ret
