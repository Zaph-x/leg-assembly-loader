	.arch armv8-a
	.file	"constants.c"
	.text
	.global	a
	.data
	.align	2
	.type	a, %object
	.size	a, 4
a:
	.word	12
	.global	b
	.align	3
	.type	b, %object
	.size	b, 8
b:
	.xword	1234567890
	.global	c
	.type	c, %object
	.size	c, 1
c:
	.byte	97
	.global	d
	.align	2
	.type	d, %object
	.size	d, 4
d:
	.word	1067320914
	.global	e
	.align	3
	.type	e, %object
	.size	e, 8
e:
	.word	1115938331
	.word	1072939210
	.global	f
	.section	.rodata
	.align	3
.LC0:
	.string	"Hello, World!"
	.section	.data.rel.local,"aw"
	.align	3
	.type	f, %object
	.size	f, 8
f:
	.xword	.LC0
	.section	.rodata
	.align	3
.LC1:
	.string	"%d"
	.align	3
.LC2:
	.string	"%ld"
	.align	3
.LC3:
	.string	"%f"
	.align	3
.LC4:
	.string	"%lf"
	.align	3
.LC5:
	.string	"%s"
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
	adrp	x0, a
	add	x0, x0, :lo12:a
	ldr	w0, [x0]
	mov	w1, w0
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
	adrp	x0, b
	add	x0, x0, :lo12:b
	ldr	x0, [x0]
	mov	x1, x0
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
	adrp	x0, c
	add	x0, x0, :lo12:c
	ldrb	w0, [x0]
	bl	putchar
	adrp	x0, d
	add	x0, x0, :lo12:d
	ldr	s0, [x0]
	fcvt	d0, s0
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	printf
	adrp	x0, e
	add	x0, x0, :lo12:e
	ldr	d0, [x0]
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	printf
	adrp	x0, f
	add	x0, x0, :lo12:f
	ldr	x0, [x0]
	mov	x1, x0
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
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
