	.file	"main.c"
	.option pic
	.text
	.section	.rodata
	.align	2
.LC0:
	.string	"Test Memory Files/prog.mem"
	.align	2
.LC1:
	.string	"-f"
	.align	2
.LC2:
	.string	"-m"
	.align	2
.LC3:
	.string	"-sp"
	.align	2
.LC4:
	.string	"-s"
	.align	2
.LC5:
	.string	"\nInvalid Arguments"
	.align	2
.LC6:
	.string	"r"
	.align	2
.LC7:
	.string	"The '%s' file provided can't be opened. Attempting to open defult file '%s'. \n"
	.align	2
.LC8:
	.string	"Error opening file"
	.align	2
.LC9:
	.string	"Address 0x%08X is out of memory bounds\n"
	.align	2
.LC10:
	.string	"%x: %x"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-272
	sw	ra,268(sp)
	sw	s0,264(sp)
	sw	s1,260(sp)
	sw	s2,256(sp)
	sw	s3,252(sp)
	sw	s4,248(sp)
	sw	s5,244(sp)
	sw	s6,240(sp)
	sw	s7,236(sp)
	sw	s8,232(sp)
	sw	s9,228(sp)
	addi	s0,sp,272
	sw	a0,-260(s0)
	sw	a1,-264(s0)
	sw	zero,-64(s0)
	sw	zero,-244(s0)
	sw	zero,-240(s0)
	sw	zero,-236(s0)
	sw	zero,-68(s0)
	li	a5,65536
	sw	a5,-72(s0)
	sw	zero,-76(s0)
	lla	a5,.LC0
	sw	a5,-80(s0)
	lw	a5,-80(s0)
	sw	a5,-56(s0)
	lw	a5,-260(s0)
	addi	a5,a5,-1
	sw	a5,-260(s0)
	lw	a5,-264(s0)
	addi	a5,a5,4
	sw	a5,-264(s0)
	j	.L2
.L8:
	lw	a5,-264(s0)
	lw	a5,0(a5)
	lla	a1,.LC1
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	bne	a5,zero,.L3
	lw	a5,-264(s0)
	lw	a5,4(a5)
	sw	a5,-56(s0)
	j	.L4
.L3:
	lw	a5,-264(s0)
	lw	a5,0(a5)
	lla	a1,.LC2
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	bne	a5,zero,.L5
	lw	a5,-264(s0)
	addi	a5,a5,4
	lw	a5,0(a5)
	mv	a0,a5
	call	atoi@plt
	sw	a0,-68(s0)
	j	.L4
.L5:
	lw	a5,-264(s0)
	lw	a5,0(a5)
	lla	a1,.LC3
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	beq	a5,zero,.L6
	lw	a5,-264(s0)
	addi	a5,a5,4
	lw	a5,0(a5)
	mv	a0,a5
	call	atoi@plt
	mv	a5,a0
	sw	a5,-72(s0)
	j	.L4
.L6:
	lw	a5,-264(s0)
	lw	a5,0(a5)
	lla	a1,.LC4
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	beq	a5,zero,.L7
	lw	a5,-264(s0)
	addi	a5,a5,4
	lw	a5,0(a5)
	mv	a0,a5
	call	atoi@plt
	mv	a5,a0
	sw	a5,-76(s0)
	j	.L4
.L7:
	lla	a0,.LC5
	call	puts@plt
	li	a0,-1
	call	exit@plt
.L4:
	lw	a5,-260(s0)
	addi	a5,a5,-2
	sw	a5,-260(s0)
	lw	a5,-264(s0)
	addi	a5,a5,8
	sw	a5,-264(s0)
.L2:
	lw	a5,-260(s0)
	bgt	a5,zero,.L8
	lla	a1,.LC6
	lw	a0,-56(s0)
	call	fopen@plt
	sw	a0,-52(s0)
	li	a5,4096
	addi	a5,a5,-2048
	sw	a5,-84(s0)
	mv	a5,sp
	mv	s1,a5
	lw	a5,-84(s0)
	addi	a5,a5,-1
	sw	a5,-88(s0)
	lw	a5,-84(s0)
	mv	s8,a5
	li	s9,0
	srli	a5,s8,27
	slli	s5,s9,5
	or	s5,a5,s5
	slli	s4,s8,5
	lw	a5,-84(s0)
	mv	s6,a5
	li	s7,0
	srli	a5,s6,27
	slli	s3,s7,5
	or	s3,a5,s3
	slli	s2,s6,5
	lw	a5,-84(s0)
	slli	a5,a5,2
	addi	a5,a5,15
	srli	a5,a5,4
	slli	a5,a5,4
	sub	sp,sp,a5
	mv	a5,sp
	addi	a5,a5,3
	srli	a5,a5,2
	slli	a5,a5,2
	sw	a5,-92(s0)
	sw	zero,-60(s0)
	j	.L9
.L10:
	lw	a4,-92(s0)
	lw	a5,-60(s0)
	slli	a5,a5,2
	add	a5,a4,a5
	sw	zero,0(a5)
	lw	a5,-60(s0)
	addi	a5,a5,1
	sw	a5,-60(s0)
.L9:
	lw	a4,-60(s0)
	lw	a5,-84(s0)
	blt	a4,a5,.L10
	lw	a5,-52(s0)
	bne	a5,zero,.L11
	la	a5,stderr
	lw	a5,0(a5)
	lw	a3,-80(s0)
	lw	a2,-56(s0)
	lla	a1,.LC7
	mv	a0,a5
	call	fprintf@plt
	lw	a5,-80(s0)
	sw	a5,-56(s0)
	lla	a1,.LC6
	lw	a0,-56(s0)
	call	fopen@plt
	sw	a0,-52(s0)
.L11:
	lw	a5,-52(s0)
	bne	a5,zero,.L12
	lla	a0,.LC8
	call	perror@plt
	li	a5,-1
	j	.L13
.L12:
	li	a5,65536
	sw	a5,-96(s0)
	j	.L14
.L16:
	lw	a4,-112(s0)
	lw	a5,-96(s0)
	bltu	a4,a5,.L15
	la	a5,stderr
	lw	a5,0(a5)
	lw	a4,-112(s0)
	mv	a2,a4
	lla	a1,.LC9
	mv	a0,a5
	call	fprintf@plt
.L15:
	lw	a5,-112(s0)
	srli	a5,a5,2
	lw	a4,-116(s0)
	lw	a3,-92(s0)
	slli	a5,a5,2
	add	a5,a3,a5
	sw	a4,0(a5)
.L14:
	addi	a4,s0,-116
	addi	a5,s0,-112
	mv	a3,a4
	mv	a2,a5
	lla	a1,.LC10
	lw	a0,-52(s0)
	call	__isoc99_fscanf@plt
	mv	a4,a0
	li	a5,2
	beq	a4,a5,.L16
	addi	a5,s0,-244
	mv	a0,a5
	call	printAllReg@plt
	li	a5,0
.L13:
	mv	sp,s1
	mv	a0,a5
	addi	sp,s0,-272
	lw	ra,268(sp)
	lw	s0,264(sp)
	lw	s1,260(sp)
	lw	s2,256(sp)
	lw	s3,252(sp)
	lw	s4,248(sp)
	lw	s5,244(sp)
	lw	s6,240(sp)
	lw	s7,236(sp)
	lw	s8,232(sp)
	lw	s9,228(sp)
	addi	sp,sp,272
	jr	ra
	.size	main, .-main
	.align	2
	.globl	printAllMem
	.type	printAllMem, @function
printAllMem:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	printAllMem, .-printAllMem
	.section	.rodata
	.align	2
.LC11:
	.string	"Register: x%02d   Contents: "
	.align	2
.LC12:
	.string	"NULL"
	.align	2
.LC13:
	.string	"%08X\n"
	.text
	.align	2
	.globl	printAllReg
	.type	printAllReg, @function
printAllReg:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	zero,-20(s0)
	j	.L21
.L24:
	lw	a1,-20(s0)
	lla	a0,.LC11
	call	printf@plt
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	li	a5,-1
	bne	a4,a5,.L22
	lla	a0,.LC12
	call	puts@plt
	j	.L23
.L22:
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	mv	a1,a5
	lla	a0,.LC13
	call	printf@plt
.L23:
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L21:
	lw	a4,-20(s0)
	li	a5,31
	ble	a4,a5,.L24
	nop
	nop
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	printAllReg, .-printAllReg
	.align	2
	.globl	readByte
	.type	readByte, @function
readByte:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	lw	a5,-44(s0)
	srai	a4,a5,31
	andi	a4,a4,3
	add	a5,a4,a5
	srai	a5,a5,2
	sw	a5,-20(s0)
	lw	a4,-44(s0)
	srai	a5,a4,31
	srli	a5,a5,30
	add	a4,a4,a5
	andi	a4,a4,3
	sub	a5,a4,a5
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-28(s0)
	lw	a5,-24(s0)
	slli	a5,a5,3
	lw	a4,-28(s0)
	srl	a5,a4,a5
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	andi	a5,a5,255
	sw	a5,-32(s0)
	lw	a5,-32(s0)
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	readByte, .-readByte
	.section	.rodata
	.align	2
.LC14:
	.string	"Misaligned reference at 0x%08d\n"
	.text
	.align	2
	.globl	readHalfWord
	.type	readHalfWord, @function
readHalfWord:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	lw	a5,-44(s0)
	andi	a5,a5,1
	beq	a5,zero,.L28
	la	a5,stderr
	lw	a5,0(a5)
	lw	a2,-44(s0)
	lla	a1,.LC14
	mv	a0,a5
	call	fprintf@plt
	li	a0,1
	call	exit@plt
.L28:
	lw	a5,-44(s0)
	srai	a4,a5,31
	andi	a4,a4,3
	add	a5,a4,a5
	srai	a5,a5,2
	sw	a5,-24(s0)
	lw	a4,-44(s0)
	srai	a5,a4,31
	srli	a5,a5,30
	add	a4,a4,a5
	andi	a4,a4,3
	sub	a5,a4,a5
	mv	a4,a5
	li	a5,2
	bne	a4,a5,.L29
	li	a5,2
	sw	a5,-20(s0)
	j	.L30
.L29:
	sw	zero,-20(s0)
.L30:
	lw	a5,-24(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	slli	a5,a5,3
	lw	a4,-28(s0)
	srl	a5,a4,a5
	sw	a5,-28(s0)
	lw	a4,-28(s0)
	li	a5,65536
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-32(s0)
	lw	a5,-32(s0)
	mv	a0,a5
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	readHalfWord, .-readHalfWord
	.align	2
	.globl	readWord
	.type	readWord, @function
readWord:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	lw	a5,-44(s0)
	srai	a4,a5,31
	andi	a4,a4,3
	add	a5,a4,a5
	srai	a5,a5,2
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-24(s0)
	lw	a5,-24(s0)
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	readWord, .-readWord
	.align	2
	.globl	writeByte
	.type	writeByte, @function
writeByte:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	sw	a3,-48(s0)
	lw	a5,-44(s0)
	srai	a4,a5,31
	andi	a4,a4,3
	add	a5,a4,a5
	srai	a5,a5,2
	sw	a5,-20(s0)
	lw	a4,-44(s0)
	srai	a5,a4,31
	srli	a5,a5,30
	add	a4,a4,a5
	andi	a4,a4,3
	sub	a5,a4,a5
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lw	a5,-24(s0)
	slli	a5,a5,3
	li	a3,255
	sll	a5,a3,a5
	not	a5,a5
	mv	a2,a5
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a3,-36(s0)
	add	a5,a3,a5
	and	a4,a4,a2
	sw	a4,0(a5)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a3,0(a5)
	lw	a5,-24(s0)
	slli	a5,a5,3
	lw	a4,-48(s0)
	sll	a4,a4,a5
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a2,-36(s0)
	add	a5,a2,a5
	or	a4,a3,a4
	sw	a4,0(a5)
	li	a5,0
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	writeByte, .-writeByte
	.align	2
	.globl	writeHalfWord
	.type	writeHalfWord, @function
writeHalfWord:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	sw	a3,-48(s0)
	lw	a5,-44(s0)
	andi	a5,a5,1
	beq	a5,zero,.L37
	la	a5,stderr
	lw	a5,0(a5)
	lw	a2,-44(s0)
	lla	a1,.LC14
	mv	a0,a5
	call	fprintf@plt
	li	a0,1
	call	exit@plt
.L37:
	lw	a5,-44(s0)
	srai	a4,a5,31
	andi	a4,a4,3
	add	a5,a4,a5
	srai	a5,a5,2
	sw	a5,-20(s0)
	lw	a4,-44(s0)
	srai	a5,a4,31
	srli	a5,a5,30
	add	a4,a4,a5
	andi	a4,a4,3
	sub	a5,a4,a5
	mv	a4,a5
	li	a5,2
	bne	a4,a5,.L38
	li	a5,2
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-32(s0)
	lw	a4,-32(s0)
	li	a5,65536
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-32(s0)
	lw	a5,-48(s0)
	slli	a5,a5,16
	sw	a5,-48(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a3,-48(s0)
	lw	a4,-32(s0)
	or	a4,a3,a4
	sw	a4,0(a5)
	j	.L39
.L38:
	sw	zero,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-28(s0)
	lw	a4,-28(s0)
	li	a5,-65536
	and	a5,a4,a5
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a3,-48(s0)
	lw	a4,-28(s0)
	or	a4,a3,a4
	sw	a4,0(a5)
.L39:
	li	a5,0
	mv	a0,a5
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	writeHalfWord, .-writeHalfWord
	.align	2
	.globl	writeWord
	.type	writeWord, @function
writeWord:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	sw	a3,-48(s0)
	lw	a5,-44(s0)
	srai	a4,a5,31
	andi	a4,a4,3
	add	a5,a4,a5
	srai	a5,a5,2
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a4,-48(s0)
	sw	a4,0(a5)
	li	a5,0
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	writeWord, .-writeWord
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
