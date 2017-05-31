GLOBAL cpuVendor
GLOBAL sti
GLOBAL setPicMaster
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL getSystemHour
EXTERN irqDispatcher
%include "./asm/macros.m"

section .text

getSystemHour:
	push rbp
	mov rbp, rsp
	mov al, 0
	out 70h, al
	in ax, 71h
	mov rsp, rbp
	pop rbp
	ret


irq0Handler:
	irqHandler 0  ---> porque si en el macros.m lo llama irqHandler 1 aca lo llama como irqHandler 0 ?

irq1Handler:
	irqHandler 1  ---> deberia ser asi el de assembler

sti:
	sti
	ret
	
setPicMaster:
	push rbp
	mov rbp, rsp
	
	mov rax, rdi    ---> que tiene el registro rdi ?
	out 21h, al
 	
	mov rsp, rbp
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
