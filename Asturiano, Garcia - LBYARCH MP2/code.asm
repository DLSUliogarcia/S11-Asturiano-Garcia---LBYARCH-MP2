section .text
bits 64
Default rel
global aSaxpy

aSaxpy:
	push rsi
	push rbp
	mov rbp, rsp
	add rbp, 16
	add rbp, 8
	mov r11d, [rbp+32]
	
	;xmm0 stores a
	;[rdx] stores Z
	;[r8] stores X
	;[r9] stores Y
	;r11d stores n
	
	;init loop counter r12d
	mov r12d, 0
	l1:

		movss xmm1, [r8]
		vmulss xmm1, xmm0, [r8 + r12*4]
		vaddss xmm3, xmm1,	[r9 + r12*4]
		movss [rdx + r12*4], xmm3

		inc r12

		cmp r12, r11
		jl l1


	pop rbp
	pop rsi
	ret
