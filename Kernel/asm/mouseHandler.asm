section .text
GLOBAL getMouseInfo
extern print

outc:
	push rbp
	mov rbp, rsp
	xor rax,rax

	out sil, dil

	mov rsp, rbp
	pop rbp
	ret

intc:
	push rbp
	mov rbp, rsp
	xor rax,rax

	in al, dil

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


