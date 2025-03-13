li a0, 85000
li a1, 1
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f3, x0
fsgnj.s f3, f1, f2
li a0, 85000
li a1, -1
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f4, x0
fsgnj.s f4, f1, f2
li a0, -85000
li a1, 1
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f5, x0
fsgnj.s f5, f1, f2
li a0, -85000
li a1, -1
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f6, x0
fsgnj.s f6, f1, f2
jr ra
