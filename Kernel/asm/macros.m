%macro pushaq 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popaq 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro


%macro irqKeyBoardHandler 1  		;----> que estaria haciendo esta macro ? y porque esta en una macro y no directamente en el libasm.asm ?
							 		;   El 1 es porque recibe 1 argumento que si vemos en irq1Handler es el 0
	pushaq           				;----> pushea registros
	

	mov rdi, %1      				;----> y estas 4 lines que harian ?
									;	   %1 significa el primer argumento, que en este caso es el 0
	call irqDispatcher

	mov al, 20h ; EOI
	out 20h, al
	
	popaq

	iretq
%endmacro
