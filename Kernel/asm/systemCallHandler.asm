GLOBAL systemHandler
EXTERN systemCallSwitcher

%include "./asm/macros.m"


systemHandler:
	pushaq
	call systemCallSwitcher
	popaq
	iretq

