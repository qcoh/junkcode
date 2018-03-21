section .text

global rread
global wwrite

rread:
	mov	r9, [rdi]
	mov	rax, r9
	ret

wwrite:
	mov	r9, rsi
	mov	[rdi], r9
