; https://www.sifflez.org/lectures/ASE/C3.pdf

section .data
	msg: db 'Hello world!', 0x0a
	length: equ $-msg

section .text
global HW
global EXIT

%macro NEXT 0
	add r15, 8
	jmp [r15]
%endmacro

EXIT:
	ret

HW:
	mov rax, 1
	mov rdi, 0
	mov rsi, msg
	mov rdx, length
	syscall
	NEXT
