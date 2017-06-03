GLOBAL mouseStart
GLOBAL getPosition

mouseStart:

exit:					;para ocultarlo mov AX, 0002h e int 33h
	ret

getPosition:
	mov AX, 0003h
	in al, 60h
	ret				;mov AX, 0003h retorno estado del cursor
					;en BX bit0=left bit1=right
					;en CX columna en DX fila