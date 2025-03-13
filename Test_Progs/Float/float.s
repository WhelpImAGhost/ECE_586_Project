	.file	"float.c"
	.option pic
	.attribute arch, "rv32i2p0_m2p0_f2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	lla	a5,.LC0
	flw	fa5,0(a5)
	fsw	fa5,-20(s0)
	lla	a5,.LC1
	flw	fa5,0(a5)
	fsw	fa5,-24(s0)
	flw	fa4,-20(s0)
	flw	fa5,-24(s0)
	fadd.s	fa5,fa4,fa5
	fsw	fa5,-28(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	2
.LC0:
	.word	1084647014
	.align	2
.LC1:
	.word	1082340147
	.ident	"GCC: (GNU) 10.2.0"
