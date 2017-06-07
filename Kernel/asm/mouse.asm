GLOBAL mouseStart
GLOBAL getPosition

mouseStart:
	call setCompaqStatusEnable

exit:					;para ocultarlo mov AX, 0002h e int 33h
	ret

setCompaqStatusEnable:	;en teoria bien
	mov al, 0x20
	out 0x64, al
	in al, 0x60	;Obtengo estado actual 
	or al, 0x02 ;Lo modifico
	and al,0xEF
	mov bl, 0x60
	out 0x64, bl ;Lo envio
	out 0x60, al

	mov cl, 0xFF	;Resetea
	out 0x64, cl
	
	leave



getPosition:
	mov AX, 0003h
	in al, 60h
	ret				;mov AX, 0003h retorno estado del cursor
					;en BX bit0=left bit1=right
					;en CX columna en DX fila