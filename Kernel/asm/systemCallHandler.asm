GLOBAL systemHandler
EXTERN systemCallSwitcher 

%include "./asm/macros.m"

;en rdi tengo fd
;en rsi tengo vector
;en rdx tengo cant bytes
;en r10 tengo el numero del switcher


systemHandler:
	pushaq
	call systemCallSwitcher
	popaq
	ret

