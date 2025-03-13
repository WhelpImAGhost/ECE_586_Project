	li a0, -5
	li a1, 5
	bne a0, a1 , .label
	jalr x0, x0, 0

.label:
	li a1, -5
	bne a0, a1, .end
.lco:
	li a0, 10
	li a1, 0
	bne a0, a1, .label
	jalr x0, x0, 0

.end:
	jalr x0, x0, 0
