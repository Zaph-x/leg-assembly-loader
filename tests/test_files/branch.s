	.arch armv8-a
	.file	"branch.c"
	.text
	.align	2
	.global	return_error
	.type	return_error, %function
return_error:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	mov	w0, 1
	bl	exit
	.cfi_endproc
.LFE6:
	.size	return_error, .-return_error
	.align	2
	.global	func
	.type	func, %function
func:
.LFB7:
	.cfi_startproc
	mov	w0, 42
	ret
	.cfi_endproc
.LFE7:
	.size	func, .-func
	.align	2
	.global	jump
	.type	jump, %function
jump:
.LFB8:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	bl	func
	nop
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8:
	.size	jump, .-jump
	.align	2
	.global	main
	.type	main, %function
main:
.LFB9:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	w0, [sp, 28]
	str	x1, [sp, 16]
	ldr	w0, [sp, 28]
	cmp	w0, 1
	bne	.L6
	bl	jump
	b	.L7
.L6:
	bl	return_error
.L7:
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
