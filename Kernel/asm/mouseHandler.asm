section .text
GLOBAL getMouseInfo
GLOBAL outc
GLOBAL inc
extern print

outc:
	push rbp
	mov rbp, rsp
	xor rax,rax

	mov rdx, rdi
	mov rax, rsi
	out dx, al

	mov rsp, rbp
	pop rbp
	ret

inc:
	push rbp
	mov rbp, rsp
	xor rax,rax

	mov rdx, rdi
	in al, dx

	mov rsp, rbp
	pop rbp
	ret

getMouseInfo:
	push rbp
	mov rbp, rsp
	xor rax,rax
	in eax,60h 	
	mov rsp, rbp
	pop rbp
	ret


