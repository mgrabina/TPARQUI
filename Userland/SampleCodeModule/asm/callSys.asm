section .text
GLOBAL callSys

callSys:
	
	push rbp
	mov rbp,rsp
	
	mov rax,rdi
	mov rdi,rsi
	mov rsi,rdx
	mov rdx,r10
	int 80h

	mov rsp,rbp
	pop rbp
	ret
	