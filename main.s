	.file	"main.c"
	.option pic
	.attribute arch, "rv32i2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata
	.align	2
.LC1:
	.string	"Mem_files/prog.mem"
	.align	2
.LC2:
	.string	"-f"
	.align	2
.LC3:
	.string	"-m"
	.align	2
.LC4:
	.string	"-sp"
	.align	2
.LC5:
	.string	"-s"
	.align	2
.LC6:
	.string	"\nInvalid Arguments"
	.align	2
.LC7:
	.string	"r"
	.align	2
.LC8:
	.string	"The '%s' file provided can't be opened. Attempting to open defult file '%s'. \n"
	.align	2
.LC9:
	.string	"Error opening file"
	.align	2
.LC10:
	.string	"Address 0x%08X is out of memory bounds\n"
	.align	2
.LC11:
	.string	"%x: %x"
	.align	2
.LC12:
	.string	"End of Program\n"
	.align	2
.LC13:
	.string	"0x%02X is an invalid op code.\n"
	.align	2
.LC0:
	.word	51
	.word	19
	.word	3
	.word	35
	.word	99
	.word	111
	.word	103
	.word	55
	.word	23
	.word	115
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-320
	sw	ra,316(sp)
	sw	s0,312(sp)
	sw	s1,308(sp)
	sw	s2,304(sp)
	sw	s3,300(sp)
	sw	s4,296(sp)
	sw	s5,292(sp)
	sw	s6,288(sp)
	sw	s7,284(sp)
	sw	s8,280(sp)
	sw	s9,276(sp)
	addi	s0,sp,320
	sw	a0,-308(s0)
	sw	a1,-312(s0)
	sw	zero,-56(s0)
	li	a5,1
	sb	a5,-49(s0)
	lla	a5,.LC0
	lw	t3,0(a5)
	lw	t1,4(a5)
	lw	a7,8(a5)
	lw	a6,12(a5)
	lw	a0,16(a5)
	lw	a1,20(a5)
	lw	a2,24(a5)
	lw	a3,28(a5)
	lw	a4,32(a5)
	lw	a5,36(a5)
	sw	t3,-164(s0)
	sw	t1,-160(s0)
	sw	a7,-156(s0)
	sw	a6,-152(s0)
	sw	a0,-148(s0)
	sw	a1,-144(s0)
	sw	a2,-140(s0)
	sw	a3,-136(s0)
	sw	a4,-132(s0)
	sw	a5,-128(s0)
	sw	zero,-292(s0)
	sw	zero,-288(s0)
	sw	zero,-284(s0)
	sw	zero,-72(s0)
	li	a5,65536
	sw	a5,-76(s0)
	sw	zero,-80(s0)
	lla	a5,.LC1
	sw	a5,-84(s0)
	lw	a5,-84(s0)
	sw	a5,-60(s0)
	lw	a5,-308(s0)
	addi	a5,a5,-1
	sw	a5,-308(s0)
	lw	a5,-312(s0)
	addi	a5,a5,4
	sw	a5,-312(s0)
	j	.L2
.L8:
	lw	a5,-312(s0)
	lw	a5,0(a5)
	lla	a1,.LC2
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	bne	a5,zero,.L3
	lw	a5,-312(s0)
	lw	a5,4(a5)
	sw	a5,-60(s0)
	j	.L4
.L3:
	lw	a5,-312(s0)
	lw	a5,0(a5)
	lla	a1,.LC3
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	bne	a5,zero,.L5
	lw	a5,-312(s0)
	addi	a5,a5,4
	lw	a5,0(a5)
	mv	a0,a5
	call	atoi@plt
	sw	a0,-72(s0)
	j	.L4
.L5:
	lw	a5,-312(s0)
	lw	a5,0(a5)
	lla	a1,.LC4
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	beq	a5,zero,.L6
	lw	a5,-312(s0)
	addi	a5,a5,4
	lw	a5,0(a5)
	mv	a0,a5
	call	atoi@plt
	mv	a5,a0
	sw	a5,-76(s0)
	j	.L4
.L6:
	lw	a5,-312(s0)
	lw	a5,0(a5)
	lla	a1,.LC5
	mv	a0,a5
	call	strcmp@plt
	mv	a5,a0
	beq	a5,zero,.L7
	lw	a5,-312(s0)
	addi	a5,a5,4
	lw	a5,0(a5)
	mv	a0,a5
	call	atoi@plt
	mv	a5,a0
	sw	a5,-80(s0)
	j	.L4
.L7:
	lla	a0,.LC6
	call	puts@plt
	li	a0,-1
	call	exit@plt
.L4:
	lw	a5,-308(s0)
	addi	a5,a5,-2
	sw	a5,-308(s0)
	lw	a5,-312(s0)
	addi	a5,a5,8
	sw	a5,-312(s0)
.L2:
	lw	a5,-308(s0)
	bgt	a5,zero,.L8
	lla	a1,.LC7
	lw	a0,-60(s0)
	call	fopen@plt
	sw	a0,-64(s0)
	li	a5,4096
	addi	a5,a5,-2048
	sw	a5,-88(s0)
	mv	a5,sp
	mv	s1,a5
	lw	a5,-88(s0)
	addi	a5,a5,-1
	sw	a5,-92(s0)
	lw	a5,-88(s0)
	mv	s8,a5
	li	s9,0
	srli	a5,s8,27
	slli	s5,s9,5
	or	s5,a5,s5
	slli	s4,s8,5
	lw	a5,-88(s0)
	mv	s6,a5
	li	s7,0
	srli	a5,s6,27
	slli	s3,s7,5
	or	s3,a5,s3
	slli	s2,s6,5
	lw	a5,-88(s0)
	slli	a5,a5,2
	addi	a5,a5,15
	srli	a5,a5,4
	slli	a5,a5,4
	sub	sp,sp,a5
	mv	a5,sp
	addi	a5,a5,3
	srli	a5,a5,2
	slli	a5,a5,2
	sw	a5,-96(s0)
	sw	zero,-68(s0)
	j	.L9
.L10:
	lw	a4,-96(s0)
	lw	a5,-68(s0)
	slli	a5,a5,2
	add	a5,a4,a5
	sw	zero,0(a5)
	lw	a5,-68(s0)
	addi	a5,a5,1
	sw	a5,-68(s0)
.L9:
	lw	a4,-68(s0)
	lw	a5,-88(s0)
	blt	a4,a5,.L10
	lw	a5,-64(s0)
	bne	a5,zero,.L11
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	lw	a3,-84(s0)
	lw	a2,-60(s0)
	lla	a1,.LC8
	mv	a0,a5
	call	fprintf@plt
	lw	a5,-84(s0)
	sw	a5,-60(s0)
	lla	a1,.LC7
	lw	a0,-60(s0)
	call	fopen@plt
	sw	a0,-64(s0)
.L11:
	lw	a5,-64(s0)
	bne	a5,zero,.L12
	lla	a0,.LC9
	call	perror@plt
	li	a5,-1
	j	.L13
.L12:
	li	a5,65536
	sw	a5,-100(s0)
	j	.L14
.L16:
	lw	a4,-116(s0)
	lw	a5,-100(s0)
	bltu	a4,a5,.L15
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	lw	a4,-116(s0)
	mv	a2,a4
	lla	a1,.LC10
	mv	a0,a5
	call	fprintf@plt
.L15:
	lw	a5,-116(s0)
	srli	a5,a5,2
	lw	a4,-120(s0)
	lw	a3,-96(s0)
	slli	a5,a5,2
	add	a5,a3,a5
	sw	a4,0(a5)
.L14:
	addi	a4,s0,-120
	addi	a5,s0,-116
	mv	a3,a4
	mv	a2,a5
	lla	a1,.LC11
	lw	a0,-64(s0)
	call	fscanf@plt
	mv	a4,a0
	li	a5,2
	beq	a4,a5,.L16
	j	.L17
.L30:
	addi	a5,s0,-124
	mv	a2,a5
	lw	a1,-56(s0)
	lw	a0,-96(s0)
	call	fetch_and_decode@plt
	lw	a5,-124(s0)
	li	a4,111
	beq	a5,a4,.L18
	li	a4,111
	bgtu	a5,a4,.L19
	li	a4,103
	beq	a5,a4,.L20
	li	a4,103
	bgtu	a5,a4,.L19
	li	a4,55
	bgtu	a5,a4,.L21
	li	a4,55
	bgtu	a5,a4,.L19
	slli	a4,a5,2
	lla	a5,.L23
	add	a5,a4,a5
	lw	a4,0(a5)
	lla	a5,.L23
	add	a5,a4,a5
	jr	a5
	.section	.rodata
	.align	2
	.align	2
.L23:
	.word	.L27-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L20-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L20-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L26-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L25-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L24-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L19-.L23
	.word	.L22-.L23
	.text
.L21:
	li	a4,99
	beq	a5,a4,.L28
	j	.L19
.L24:
	addi	a5,s0,-292
	mv	a3,a5
	lw	a2,-56(s0)
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	r_type@plt
	j	.L29
.L20:
	addi	a5,s0,-292
	mv	a3,a5
	lw	a2,-56(s0)
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	i_type@plt
	j	.L29
.L25:
	addi	a5,s0,-292
	mv	a3,a5
	lw	a2,-56(s0)
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	s_type@plt
	j	.L29
.L28:
	addi	a5,s0,-292
	mv	a3,a5
	lw	a2,-56(s0)
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	b_type@plt
	j	.L29
.L18:
	addi	a5,s0,-292
	mv	a3,a5
	lw	a2,-56(s0)
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	j_type@plt
	j	.L29
.L22:
	addi	a5,s0,-292
	mv	a3,a5
	lw	a2,-56(s0)
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	u_type@plt
.L26:
	addi	a5,s0,-292
	mv	a3,a5
	lw	a2,-56(s0)
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	u_type@plt
	j	.L29
.L27:
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	mv	a3,a5
	li	a2,15
	li	a1,1
	lla	a0,.LC12
	call	fwrite@plt
	sb	zero,-49(s0)
	j	.L29
.L19:
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	lw	a4,-124(s0)
	mv	a2,a4
	lla	a1,.LC13
	mv	a0,a5
	call	fprintf@plt
	li	a0,1
	call	exit@plt
.L29:
	lw	a5,-56(s0)
	addi	a5,a5,4
	sw	a5,-56(s0)
.L17:
	lbu	a5,-49(s0)
	bne	a5,zero,.L30
	lw	a1,-88(s0)
	lw	a0,-96(s0)
	call	printAllMem@plt
	addi	a5,s0,-292
	mv	a0,a5
	call	printAllReg@plt
	li	a5,0
.L13:
	mv	sp,s1
	mv	a0,a5
	addi	sp,s0,-320
	lw	ra,316(sp)
	lw	s0,312(sp)
	lw	s1,308(sp)
	lw	s2,304(sp)
	lw	s3,300(sp)
	lw	s4,296(sp)
	lw	s5,292(sp)
	lw	s6,288(sp)
	lw	s7,284(sp)
	lw	s8,280(sp)
	lw	s9,276(sp)
	addi	sp,sp,320
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
.LC14:
	.string	"Register: x%02d   Contents: "
	.align	2
.LC15:
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
	j	.L35
.L36:
	lw	a1,-20(s0)
	lla	a0,.LC14
	call	printf@plt
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	mv	a1,a5
	lla	a0,.LC15
	call	printf@plt
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L35:
	lw	a4,-20(s0)
	li	a5,31
	ble	a4,a5,.L36
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
.LC16:
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
	beq	a5,zero,.L40
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	lw	a2,-44(s0)
	lla	a1,.LC16
	mv	a0,a5
	call	fprintf@plt
	li	a0,1
	call	exit@plt
.L40:
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
	bne	a4,a5,.L41
	li	a5,2
	sw	a5,-20(s0)
	j	.L42
.L41:
	sw	zero,-20(s0)
.L42:
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
	beq	a5,zero,.L49
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	lw	a2,-44(s0)
	lla	a1,.LC16
	mv	a0,a5
	call	fprintf@plt
	li	a0,1
	call	exit@plt
.L49:
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
	bne	a4,a5,.L50
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
	j	.L51
.L50:
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
.L51:
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
	.align	2
	.globl	fetch_and_decode
	.type	fetch_and_decode, @function
fetch_and_decode:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	lw	a5,-40(s0)
	andi	a5,a5,-4
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	andi	a4,a5,127
	lw	a5,-44(s0)
	sw	a4,0(a5)
	nop
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	fetch_and_decode, .-fetch_and_decode
	.align	2
	.globl	r_type
	.type	r_type, @function
r_type:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	sw	a3,-48(s0)
	lw	a5,-44(s0)
	andi	a5,a5,-4
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	andi	a5,a5,0xff
	andi	a5,a5,127
	sb	a5,-21(s0)
	lw	a5,-20(s0)
	srli	a5,a5,7
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-22(s0)
	lw	a5,-20(s0)
	srli	a5,a5,12
	andi	a5,a5,0xff
	andi	a5,a5,7
	sb	a5,-23(s0)
	lw	a5,-20(s0)
	srli	a5,a5,15
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-24(s0)
	lw	a5,-20(s0)
	srli	a5,a5,20
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-25(s0)
	lw	a5,-20(s0)
	srli	a5,a5,25
	sb	a5,-26(s0)
	nop
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	r_type, .-r_type
	.section	.rodata
	.align	2
.LC17:
	.string	"0x%02X is not a valid I-type opcode.\n"
	.text
	.align	2
	.globl	i_type
	.type	i_type, @function
i_type:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	sw	a3,-48(s0)
	lw	a5,-44(s0)
	andi	a5,a5,-4
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-24(s0)
	lw	a5,-24(s0)
	andi	a5,a5,0xff
	andi	a5,a5,127
	sb	a5,-25(s0)
	lw	a5,-24(s0)
	srli	a5,a5,7
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-26(s0)
	lw	a5,-24(s0)
	srli	a5,a5,12
	andi	a5,a5,0xff
	andi	a5,a5,7
	sb	a5,-27(s0)
	lw	a5,-24(s0)
	srli	a5,a5,15
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-28(s0)
	lw	a5,-24(s0)
	srli	a5,a5,20
	sh	a5,-18(s0)
	lh	a5,-18(s0)
	srai	a5,a5,11
	slli	a5,a5,16
	srai	a5,a5,16
	slli	a5,a5,16
	srli	a5,a5,16
	andi	a5,a5,1
	sw	a5,-32(s0)
	lw	a4,-32(s0)
	li	a5,1
	bne	a4,a5,.L60
	lhu	a4,-18(s0)
	li	a5,-4096
	or	a5,a4,a5
	slli	a5,a5,16
	srli	a5,a5,16
	sh	a5,-18(s0)
	j	.L61
.L60:
	lhu	a4,-18(s0)
	li	a5,4096
	addi	a5,a5,-1
	and	a5,a4,a5
	sh	a5,-18(s0)
.L61:
	lbu	a5,-25(s0)
	li	a4,103
	beq	a5,a4,.L68
	li	a4,103
	bgt	a5,a4,.L63
	li	a4,3
	beq	a5,a4,.L64
	li	a4,19
	beq	a5,a4,.L69
	j	.L63
.L64:
	lhu	a3,-18(s0)
	lbu	a2,-28(s0)
	lbu	a1,-26(s0)
	lbu	a0,-27(s0)
	lw	a6,-48(s0)
	lw	a5,-40(s0)
	lw	a4,-36(s0)
	call	load@plt
	j	.L66
.L63:
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	lbu	a4,-25(s0)
	mv	a2,a4
	lla	a1,.LC17
	mv	a0,a5
	call	fprintf@plt
	li	a0,1
	call	exit@plt
.L68:
	nop
	j	.L66
.L69:
	nop
.L66:
	nop
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	i_type, .-i_type
	.align	2
	.globl	immediateop
	.type	immediateop, @function
immediateop:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a4,-28(s0)
	sw	a5,-32(s0)
	sw	a6,-36(s0)
	mv	a5,a0
	sb	a5,-17(s0)
	mv	a5,a1
	sb	a5,-18(s0)
	mv	a5,a2
	sb	a5,-19(s0)
	mv	a5,a3
	sh	a5,-22(s0)
	lbu	a5,-17(s0)
	li	a4,7
	bgtu	a5,a4,.L82
	slli	a4,a5,2
	lla	a5,.L73
	add	a5,a4,a5
	lw	a4,0(a5)
	lla	a5,.L73
	add	a5,a4,a5
	jr	a5
	.section	.rodata
	.align	2
	.align	2
.L73:
	.word	.L83-.L73
	.word	.L83-.L73
	.word	.L83-.L73
	.word	.L83-.L73
	.word	.L83-.L73
	.word	.L83-.L73
	.word	.L83-.L73
	.word	.L83-.L73
	.text
.L82:
	nop
	j	.L84
.L83:
	nop
.L84:
	nop
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	immediateop, .-immediateop
	.section	.rodata
	.align	2
.LC18:
	.string	"The provided load instruction is invalid."
	.text
	.align	2
	.globl	load
	.type	load, @function
load:
	addi	sp,sp,-64
	sw	ra,60(sp)
	sw	s0,56(sp)
	addi	s0,sp,64
	sw	a4,-44(s0)
	sw	a5,-48(s0)
	sw	a6,-52(s0)
	mv	a5,a0
	sb	a5,-33(s0)
	mv	a5,a1
	sb	a5,-34(s0)
	mv	a5,a2
	sb	a5,-35(s0)
	mv	a5,a3
	sh	a5,-38(s0)
	lbu	a5,-33(s0)
	li	a4,5
	bgtu	a5,a4,.L86
	slli	a4,a5,2
	lla	a5,.L88
	add	a5,a4,a5
	lw	a4,0(a5)
	lla	a5,.L88
	add	a5,a4,a5
	jr	a5
	.section	.rodata
	.align	2
	.align	2
.L88:
	.word	.L92-.L88
	.word	.L91-.L88
	.word	.L90-.L88
	.word	.L86-.L88
	.word	.L89-.L88
	.word	.L87-.L88
	.text
.L92:
	lbu	a5,-35(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lhu	a5,-38(s0)
	add	a5,a4,a5
	mv	a2,a5
	lw	a1,-48(s0)
	lw	a0,-44(s0)
	call	readByte@plt
	sw	a0,-20(s0)
	lw	a5,-20(s0)
	srli	a5,a5,7
	andi	a5,a5,1
	sw	a5,-24(s0)
	lw	a4,-24(s0)
	li	a5,1
	bne	a4,a5,.L93
	lw	a5,-20(s0)
	ori	a5,a5,-256
	sw	a5,-20(s0)
	j	.L94
.L93:
	lw	a5,-20(s0)
	andi	a5,a5,255
	sw	a5,-20(s0)
.L94:
	lbu	a5,-34(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a4,-20(s0)
	sw	a4,0(a5)
	j	.L95
.L91:
	lbu	a5,-35(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lhu	a5,-38(s0)
	add	a5,a4,a5
	mv	a2,a5
	lw	a1,-48(s0)
	lw	a0,-44(s0)
	call	readHalfWord@plt
	sw	a0,-20(s0)
	lw	a5,-20(s0)
	srli	a5,a5,15
	andi	a5,a5,1
	sw	a5,-24(s0)
	lw	a4,-24(s0)
	li	a5,1
	bne	a4,a5,.L96
	lw	a4,-20(s0)
	li	a5,-65536
	or	a5,a4,a5
	sw	a5,-20(s0)
	j	.L97
.L96:
	lw	a4,-20(s0)
	li	a5,65536
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-20(s0)
.L97:
	lbu	a5,-34(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a4,-20(s0)
	sw	a4,0(a5)
	j	.L95
.L90:
	lbu	a5,-35(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lhu	a5,-38(s0)
	add	a5,a4,a5
	mv	a2,a5
	lw	a1,-48(s0)
	lw	a0,-44(s0)
	call	readWord@plt
	mv	a3,a0
	lbu	a5,-34(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	mv	a4,a3
	sw	a4,0(a5)
	j	.L95
.L89:
	lbu	a5,-35(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lhu	a5,-38(s0)
	add	a5,a4,a5
	mv	a2,a5
	lw	a1,-48(s0)
	lw	a0,-44(s0)
	call	readByte@plt
	sw	a0,-20(s0)
	lw	a4,-20(s0)
	lbu	a5,-34(s0)
	slli	a5,a5,2
	lw	a3,-52(s0)
	add	a5,a3,a5
	andi	a4,a4,255
	sw	a4,0(a5)
	j	.L95
.L87:
	lbu	a5,-35(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lhu	a5,-38(s0)
	add	a5,a4,a5
	mv	a2,a5
	lw	a1,-48(s0)
	lw	a0,-44(s0)
	call	readHalfWord@plt
	sw	a0,-20(s0)
	lw	a3,-20(s0)
	lbu	a5,-34(s0)
	slli	a5,a5,2
	lw	a4,-52(s0)
	add	a5,a4,a5
	li	a4,65536
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	j	.L95
.L86:
	lla	a0,.LC18
	call	puts@plt
	li	a0,1
	call	exit@plt
.L95:
	nop
	lw	ra,60(sp)
	lw	s0,56(sp)
	addi	sp,sp,64
	jr	ra
	.size	load, .-load
	.section	.rodata
	.align	2
.LC19:
	.string	"0x%02X is not a valid S-type Function3 value.\n"
	.text
	.align	2
	.globl	s_type
	.type	s_type, @function
s_type:
	addi	sp,sp,-64
	sw	ra,60(sp)
	sw	s0,56(sp)
	addi	s0,sp,64
	sw	a0,-52(s0)
	sw	a1,-56(s0)
	sw	a2,-60(s0)
	sw	a3,-64(s0)
	lw	a5,-60(s0)
	andi	a5,a5,-4
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-24(s0)
	lw	a5,-24(s0)
	andi	a5,a5,0xff
	andi	a5,a5,127
	sb	a5,-25(s0)
	lw	a5,-24(s0)
	srli	a5,a5,7
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-26(s0)
	lw	a5,-24(s0)
	srli	a5,a5,12
	andi	a5,a5,0xff
	andi	a5,a5,7
	sb	a5,-27(s0)
	lw	a5,-24(s0)
	srli	a5,a5,15
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-28(s0)
	lw	a5,-24(s0)
	srli	a5,a5,20
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-29(s0)
	lw	a5,-24(s0)
	srli	a5,a5,25
	sb	a5,-30(s0)
	lbu	a5,-30(s0)
	slli	a5,a5,16
	srli	a5,a5,16
	slli	a5,a5,5
	slli	a4,a5,16
	srli	a4,a4,16
	lbu	a5,-26(s0)
	slli	a5,a5,16
	srli	a5,a5,16
	add	a5,a4,a5
	slli	a5,a5,16
	srli	a5,a5,16
	sh	a5,-18(s0)
	lh	a5,-18(s0)
	srai	a5,a5,11
	slli	a5,a5,16
	srai	a5,a5,16
	slli	a5,a5,16
	srli	a5,a5,16
	andi	a5,a5,1
	sw	a5,-36(s0)
	lw	a4,-36(s0)
	li	a5,1
	bne	a4,a5,.L100
	lhu	a4,-18(s0)
	li	a5,-4096
	or	a5,a4,a5
	slli	a5,a5,16
	srli	a5,a5,16
	sh	a5,-18(s0)
	j	.L101
.L100:
	lhu	a4,-18(s0)
	li	a5,4096
	addi	a5,a5,-1
	and	a5,a4,a5
	sh	a5,-18(s0)
.L101:
	lbu	a5,-27(s0)
	li	a4,2
	beq	a5,a4,.L102
	li	a4,2
	bgt	a5,a4,.L103
	beq	a5,zero,.L104
	li	a4,1
	beq	a5,a4,.L105
	j	.L103
.L104:
	lbu	a5,-28(s0)
	slli	a5,a5,2
	lw	a4,-64(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lh	a5,-18(s0)
	add	a2,a4,a5
	lbu	a5,-29(s0)
	slli	a5,a5,2
	lw	a4,-64(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	mv	a3,a5
	lw	a1,-56(s0)
	lw	a0,-52(s0)
	call	writeByte@plt
	j	.L106
.L105:
	lbu	a5,-28(s0)
	slli	a5,a5,2
	lw	a4,-64(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lh	a5,-18(s0)
	add	a2,a4,a5
	lbu	a5,-29(s0)
	slli	a5,a5,2
	lw	a4,-64(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	mv	a3,a5
	lw	a1,-56(s0)
	lw	a0,-52(s0)
	call	writeHalfWord@plt
	j	.L106
.L102:
	lbu	a5,-28(s0)
	slli	a5,a5,2
	lw	a4,-64(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	lh	a5,-18(s0)
	add	a2,a4,a5
	lbu	a5,-29(s0)
	slli	a5,a5,2
	lw	a4,-64(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	mv	a3,a5
	lw	a1,-56(s0)
	lw	a0,-52(s0)
	call	writeWord@plt
	j	.L106
.L103:
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	lbu	a4,-27(s0)
	mv	a2,a4
	lla	a1,.LC19
	mv	a0,a5
	call	fprintf@plt
.L106:
	nop
	lw	ra,60(sp)
	lw	s0,56(sp)
	addi	sp,sp,64
	jr	ra
	.size	s_type, .-s_type
	.align	2
	.globl	b_type
	.type	b_type, @function
b_type:
	addi	sp,sp,-64
	sw	s0,60(sp)
	addi	s0,sp,64
	sw	a0,-52(s0)
	sw	a1,-56(s0)
	sw	a2,-60(s0)
	sw	a3,-64(s0)
	lw	a5,-60(s0)
	andi	a5,a5,-4
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	andi	a5,a5,0xff
	andi	a5,a5,127
	sb	a5,-21(s0)
	lw	a5,-20(s0)
	srli	a5,a5,8
	andi	a5,a5,0xff
	andi	a5,a5,15
	sb	a5,-22(s0)
	lw	a5,-20(s0)
	srli	a5,a5,7
	andi	a5,a5,0xff
	andi	a5,a5,1
	sb	a5,-23(s0)
	lw	a5,-20(s0)
	srli	a5,a5,12
	andi	a5,a5,0xff
	andi	a5,a5,7
	sb	a5,-24(s0)
	lw	a5,-20(s0)
	srli	a5,a5,15
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-25(s0)
	lw	a5,-20(s0)
	srli	a5,a5,20
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-26(s0)
	lw	a5,-20(s0)
	srli	a5,a5,25
	andi	a5,a5,0xff
	andi	a5,a5,63
	sb	a5,-27(s0)
	lw	a5,-20(s0)
	srli	a5,a5,31
	sb	a5,-28(s0)
	lbu	a5,-28(s0)
	slli	a5,a5,16
	srli	a5,a5,16
	slli	a5,a5,12
	slli	a4,a5,16
	srli	a4,a4,16
	lbu	a5,-23(s0)
	slli	a5,a5,16
	srli	a5,a5,16
	slli	a5,a5,11
	slli	a5,a5,16
	srli	a5,a5,16
	add	a5,a4,a5
	slli	a4,a5,16
	srli	a4,a4,16
	lbu	a5,-27(s0)
	slli	a5,a5,16
	srli	a5,a5,16
	slli	a5,a5,5
	slli	a5,a5,16
	srli	a5,a5,16
	add	a5,a4,a5
	slli	a4,a5,16
	srli	a4,a4,16
	lbu	a5,-22(s0)
	slli	a5,a5,16
	srli	a5,a5,16
	slli	a5,a5,1
	slli	a5,a5,16
	srli	a5,a5,16
	add	a5,a4,a5
	slli	a5,a5,16
	srli	a5,a5,16
	sh	a5,-30(s0)
	lh	a5,-30(s0)
	srai	a5,a5,12
	slli	a5,a5,16
	srai	a5,a5,16
	slli	a5,a5,16
	srli	a5,a5,16
	andi	a5,a5,1
	sw	a5,-36(s0)
	lw	a4,-36(s0)
	li	a5,1
	bne	a4,a5,.L109
	lhu	a4,-30(s0)
	li	a5,-8192
	or	a5,a4,a5
	slli	a5,a5,16
	srli	a5,a5,16
	sh	a5,-30(s0)
	j	.L108
.L109:
	lhu	a4,-30(s0)
	li	a5,8192
	addi	a5,a5,-1
	and	a5,a4,a5
	sh	a5,-30(s0)
	nop
.L108:
	lw	s0,60(sp)
	addi	sp,sp,64
	jr	ra
	.size	b_type, .-b_type
	.section	.rodata
	.align	2
.LC20:
	.string	"Invalid U-type instruction.\n"
	.text
	.align	2
	.globl	u_type
	.type	u_type, @function
u_type:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	sw	a3,-48(s0)
	lw	a5,-44(s0)
	andi	a5,a5,-4
	lw	a4,-36(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	andi	a5,a5,0xff
	andi	a5,a5,127
	sb	a5,-21(s0)
	lw	a5,-20(s0)
	srli	a5,a5,7
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-22(s0)
	lw	a4,-20(s0)
	li	a5,-4096
	and	a5,a4,a5
	sw	a5,-28(s0)
	lbu	a5,-21(s0)
	li	a4,23
	beq	a5,a4,.L113
	li	a4,55
	bne	a5,a4,.L114
	lbu	a5,-22(s0)
	slli	a5,a5,2
	lw	a4,-48(s0)
	add	a5,a4,a5
	lw	a4,-28(s0)
	slli	a4,a4,12
	sw	a4,0(a5)
	j	.L115
.L113:
	lw	a5,-28(s0)
	slli	a5,a5,12
	mv	a4,a5
	lw	a5,-44(s0)
	add	a3,a4,a5
	lbu	a5,-22(s0)
	slli	a5,a5,2
	lw	a4,-48(s0)
	add	a5,a4,a5
	mv	a4,a3
	sw	a4,0(a5)
	j	.L115
.L114:
	la	a5,_impure_ptr
	lw	a5,0(a5)
	lw	a5,12(a5)
	mv	a3,a5
	li	a2,28
	li	a1,1
	lla	a0,.LC20
	call	fwrite@plt
	nop
.L115:
	nop
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	u_type, .-u_type
	.align	2
	.globl	j_type
	.type	j_type, @function
j_type:
	addi	sp,sp,-64
	sw	s0,60(sp)
	addi	s0,sp,64
	sw	a0,-52(s0)
	sw	a1,-56(s0)
	sw	a2,-60(s0)
	sw	a3,-64(s0)
	lw	a5,-60(s0)
	andi	a5,a5,-4
	lw	a4,-52(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	andi	a5,a5,0xff
	andi	a5,a5,127
	sb	a5,-21(s0)
	lw	a5,-20(s0)
	srli	a5,a5,7
	andi	a5,a5,0xff
	andi	a5,a5,31
	sb	a5,-22(s0)
	lw	a5,-20(s0)
	srli	a5,a5,12
	sw	a5,-28(s0)
	lw	a4,-28(s0)
	li	a5,524288
	and	a5,a4,a5
	sw	a5,-32(s0)
	lw	a5,-28(s0)
	srai	a5,a5,9
	andi	a5,a5,1023
	sw	a5,-36(s0)
	lw	a5,-28(s0)
	srai	a5,a5,8
	slli	a5,a5,10
	andi	a5,a5,1024
	sw	a5,-40(s0)
	lw	a5,-28(s0)
	slli	a5,a5,11
	mv	a4,a5
	li	a5,524288
	addi	a5,a5,-2048
	and	a5,a4,a5
	sw	a5,-44(s0)
	lw	a4,-32(s0)
	lw	a5,-44(s0)
	add	a4,a4,a5
	lw	a5,-40(s0)
	add	a4,a4,a5
	lw	a5,-36(s0)
	add	a5,a4,a5
	slli	a5,a5,1
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	srai	a5,a5,20
	andi	a5,a5,1
	sw	a5,-48(s0)
	lw	a4,-48(s0)
	li	a5,1
	bne	a4,a5,.L118
	lw	a4,-28(s0)
	li	a5,-2097152
	or	a5,a4,a5
	sw	a5,-28(s0)
	j	.L117
.L118:
	lw	a4,-28(s0)
	li	a5,2097152
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-28(s0)
	nop
.L117:
	lw	s0,60(sp)
	addi	sp,sp,64
	jr	ra
	.size	j_type, .-j_type
	.ident	"GCC: (GNU) 10.2.0"
