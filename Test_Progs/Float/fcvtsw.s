li a0, 0
fcvt.s.w f1, a0
li a0, -25000
fcvt.s.w f2, a0
li a0, 25000
fcvt.s.w f3, a0
lw a0, 0x80(x0)
fcvt.s.w f4, a0
jr ra
