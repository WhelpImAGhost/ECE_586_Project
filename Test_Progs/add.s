	.file	"add.c"
	.option pic
	.attribute arch, "rv32i2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	adder
	.type	adder, @function
adder:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	li	a5,1
	sw	a5,-20(s0)
	li	a5,3
	sw	a5,-24(s0)
	li	a5,4
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	addi	a5,a5,10
	sw	a5,-32(s0)
	lw	a4,-24(s0)
	lw	a5,-28(s0)
	add	a5,a4,a5
	sw	a5,-36(s0)
	nop
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	adder, .-adder
	.ident	"GCC: (GNU) 10.2.0"
