section .text
GLOBAL getMouseInfo
GLOBAL startMouse
extern print

startMouse:	;en teoria bien
	push rbp
	mov rbp, rsp
	xor rax,rax

	mov al, 0x20
	out 0x64, al
	in al, 0x60	;Obtengo estado actual 
	or al, 0x02 ;Lo modifico
	and al,0xEF
	mov bl, 0x60
	out 0x64, 0x60 ;Lo envio
	out 0x60, al

	mov cl, 0xFF	;Resetea
	out 0x64, 0xFF
	
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


