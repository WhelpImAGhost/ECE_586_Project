li a0, 1000
li a1, 25
fcvt.s.wu f1, a0
fcvt.s.wu f2, a1
fcvt.s.wu f3, x0
fsgnjx.s f3, f1, f2
li a0, 1000
li a1, -1000
fcvt.s.wu f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f4, x0
fsgnjx.s f4, f1, f2
li a0, -1000
li a1, 1000
fcvt.s.w f1, a0
fcvt.s.wu f2, a1
fcvt.s.wu f5, x0
fsgnjx.s f5, f1, f2
li a0, -1000
li a1, -1000
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f6, x0
fsgnjx.s f6, f1, f2
jr ra
