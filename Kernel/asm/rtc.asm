GLOBAL getSeconds
GLOBAL getMinutes
GLOBAL getHours
GLOBAL getWeekDay
GLOBAL getDayMonth
GLOBAL getMonth
GLOBAL getYear
GLOBAL translate
GLOBAL rtcInit
section .text


translate:
	push rbx

	mov rbx, rdi
	and rbx, 0xFFFF ;16 bits

	mov rax, rsi

	mov dx, bx
	in al, dx
	and rax, 0xff;
	
	pop rbx

	ret


rtcInit:
	push rbx
	push rax 

	mov rbx, rdi
	and rbx, 0xFFFF ;16 bits

	mov rax, rsi

	mov dx, bx
	out dx, al
	

	pop rax
	pop rbx
	ret


getSeconds:
	
	mov al, 0
	out 70h, al
	xor rax,rax
	in ax, 71h

	ret


getMinutes:
	
	mov al, 2
	out 70h, al
	xor rax,rax
	in ax, 71h

	ret	

getHours:
	
	mov al, 4
	out 70h, al
	xor rax,rax
	in ax, 71h

	ret	

getWeekDay:

	mov al, 6
	out 70h, al
	xor rax,rax
	in ax, 71h

	ret	

getDayMonth:

	mov al, 7
	out 70h, al
	xor rax,rax
	in ax, 71h

	ret	

getMonth: 

	mov al, 8
	out 70h, al
	xor rax,rax
	in ax, 71h

	ret	

getYear:

	mov al, 9
	out 70h, al
	xor rax,rax
	in ax, 71h

	ret	 
