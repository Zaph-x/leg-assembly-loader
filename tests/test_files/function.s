	.arch armv8-a
	.file	"function.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"This function returns nothing"
	.text
	.align	2
	.global	returnNothing
	.type	returnNothing, %function
returnNothing:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	nop
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	returnNothing, .-returnNothing
	.align	2
	.global	returnInt8
	.type	returnInt8, %function
returnInt8:
.LFB1:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	ldrsb	w0, [sp, 15]
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE1:
	.size	returnInt8, .-returnInt8
	.align	2
	.global	returnInt16
	.type	returnInt16, %function
returnInt16:
.LFB2:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	ldrsh	w0, [sp, 14]
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE2:
	.size	returnInt16, .-returnInt16
	.align	2
	.global	returnInt32
	.type	returnInt32, %function
returnInt32:
.LFB3:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	ldr	w0, [sp, 12]
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE3:
	.size	returnInt32, .-returnInt32
	.align	2
	.global	returnInt64
	.type	returnInt64, %function
returnInt64:
.LFB4:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	ldr	x0, [sp, 8]
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE4:
	.size	returnInt64, .-returnInt64
	.align	2
	.global	returnChar
	.type	returnChar, %function
returnChar:
.LFB5:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	ldrb	w0, [sp, 15]
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE5:
	.size	returnChar, .-returnChar
	.align	2
	.global	returnFloat
	.type	returnFloat, %function
returnFloat:
.LFB6:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	ldr	w0, [sp, 12]
	fmov	s0, w0
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	returnFloat, .-returnFloat
	.align	2
	.global	returnDouble
	.type	returnDouble, %function
returnDouble:
.LFB7:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	ldr	x0, [sp, 8]
	fmov	d0, x0
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE7:
	.size	returnDouble, .-returnDouble
	.align	2
	.global	main
	.type	main, %function
main:
.LFB8:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	bl	returnNothing
	bl	returnInt8
	bl	returnInt16
	bl	returnInt32
	bl	returnInt64
	bl	returnFloat
	bl	returnChar
	bl	returnDouble
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
