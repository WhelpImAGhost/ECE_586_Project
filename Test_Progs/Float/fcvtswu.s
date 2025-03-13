li a0, 0
fcvt.s.wu f1, a0
li a0, -25000
fcvt.s.wu f2, a0
li a0, 25000
fcvt.s.wu f3, a0
lw a0, 0x80(x0)
fcvt.s.wu f4, a0
jr ra
