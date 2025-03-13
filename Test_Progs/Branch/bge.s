
li a0, 1
li a1, 5
bge a0, a1, .end
li a0, -10
li a1, 5
bge a0, a1, .end
li a0, -10
li a1, -5
bge a0, a1, .end
li a0, 5
li a1, 5
bge a0, a1, .lc0
j .end

.lc0:
li a0, -12
li a1, -12
bge a0, a1, .lc1
j .end

.lc1:
li a0, -1
li a1, -5
bge a0, a1, .lc2
j .end

.lc2:
li a0, 10
li a1, -5
bge a0, a1, .lc3
j .end

.lc3:
li a0, 10
li a1, 5
bge a0, a1, .end
addi x0, x0, 0
j .end

.end:
jr x0
