	.arch armv8-a
	.file	"imperial_distance.c"
	.text
	.comm	d1,8,8
	.comm	d2,8,8
	.comm	result,8,8
	.section	.rodata
	.align	3
.LC0:
	.string	"Enter 1st distance"
	.align	3
.LC1:
	.string	"Enter feet: "
	.align	3
.LC2:
	.string	"%d"
	.align	3
.LC3:
	.string	"Enter inch: "
	.align	3
.LC4:
	.string	"%f"
	.align	3
.LC5:
	.string	"\nEnter 2nd distance"
	.align	3
.LC6:
	.string	"\nSum of distances = %d'-%.1f\""
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	puts
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
	adrp	x0, :got:d1
	ldr	x1, [x0, #:got_lo12:d1]
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	__isoc99_scanf
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	printf
	adrp	x0, :got:d1
	ldr	x0, [x0, #:got_lo12:d1]
	add	x1, x0, 4
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	__isoc99_scanf
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	puts
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
	adrp	x0, :got:d2
	ldr	x1, [x0, #:got_lo12:d2]
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	__isoc99_scanf
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	printf
	adrp	x0, :got:d2
	ldr	x0, [x0, #:got_lo12:d2]
	add	x1, x0, 4
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	__isoc99_scanf
	adrp	x0, :got:d1
	ldr	x0, [x0, #:got_lo12:d1]
	ldr	w1, [x0]
	adrp	x0, :got:d2
	ldr	x0, [x0, #:got_lo12:d2]
	ldr	w0, [x0]
	add	w1, w1, w0
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	str	w1, [x0]
	adrp	x0, :got:d1
	ldr	x0, [x0, #:got_lo12:d1]
	ldr	s1, [x0, 4]
	adrp	x0, :got:d2
	ldr	x0, [x0, #:got_lo12:d2]
	ldr	s0, [x0, 4]
	fadd	s0, s1, s0
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	str	s0, [x0, 4]
	b	.L2
.L3:
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	ldr	s1, [x0, 4]
	fmov	s0, 1.2e+1
	fsub	s0, s1, s0
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	str	s0, [x0, 4]
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	ldr	w0, [x0]
	add	w1, w0, 1
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	str	w1, [x0]
.L2:
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	ldr	s1, [x0, 4]
	fmov	s0, 1.2e+1
	fcmpe	s1, s0
	bge	.L3
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	ldr	w1, [x0]
	adrp	x0, :got:result
	ldr	x0, [x0, #:got_lo12:result]
	ldr	s0, [x0, 4]
	fcvt	d0, s0
	adrp	x0, .LC6
	add	x0, x0, :lo12:.LC6
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
