GLOBAL cpuVendor
GLOBAL sti
GLOBAL cli
GLOBAL setPicMaster
GLOBAL setPicSlave
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL irq12Handler

EXTERN irqDispatcher
extern print
%include "./asm/macros.m"

section .text



irq0Handler:
	irqHandler 0

irq1Handler:
	irqHandler 1

irq12Handler:
	irqHandler 2
		

sti:
	sti
	ret
cli:
	cli
	ret
	
setPicMaster:
	push rbp
	mov rbp, rsp
	
	mov rax, rdi
	out 21h, al
	
	mov rsp, rbp
	pop rbp
	ret
setPicSlave:
	push rbp
	mov rbp, rsp

	mov rax,rdi
	out 0A1h,al

	pop rbp
	ret
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
