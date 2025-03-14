li a0, 1
li a1, 5
bltu a0, a1, .lc0
jr x0


.lc0:
li a0, -10
li a1, 5
bltu a0, a1, .end

.lc1:
li a0, -10
li a1, -5
bltu a0, a1, .lc2

.lc2:

li a0, 5
li a1, 5
bltu a0, a1, .end
li a0, -1
li a1, -5
bltu a0, a1, .end
li a0, 10
li a1, -5
bltu a0, a1, .lc3
jr x0

.lc3:
li a0, 10
li a1, 5
bltu a0, a1, .end
addi x0, x0, 0

.end:
jr x0
