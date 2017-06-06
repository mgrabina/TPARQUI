section .text
GLOBAL getMouseInfo
extern print
getMouseInfo:
	push rbp
	mov rbp, rsp
	xor rax,rax
	call print
	in eax,60h 	
	mov rsp, rbp
	pop rbp
	ret
