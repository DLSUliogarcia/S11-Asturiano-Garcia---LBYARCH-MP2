section .data

section .text
	bits 64
	default rel
	global aSaxpy

aSaxpy:
	xorps xmm0, xmm0	; A
	xorps xmm1, xmm1	; [X]
	xorps xmm2, xmm2	; [Y]
	
	push rbp
	mov rbp, rsp
	add rbp, 16				; Push rbp (+8) and Return Address of Call (+8)
	movss xmm0, [rbp+32]	; 5th Parameter, +32 because of Shadow RAM

	inc rcx

	l1:
		movss xmm1, [r8]	; Current X
		movss xmm2, [r9]	; Current Y

		mulss xmm1, xmm0			; A*X[i]
		addss xmm2, xmm1			; A*X[i] + Y[i]
		movss dword [rdx], xmm2		; Z[i] = A*X[i] + Y[i]

		; Increment Pointers
		add r8, 4
		add r9, 4
		add rdx, 4

		loop l1

	ret
