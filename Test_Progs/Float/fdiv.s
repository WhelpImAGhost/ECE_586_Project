li a0, 6
li a1, 6
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f3, x0
fdiv.s f3, f1, f2
li a0, 6
li a1, -2
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f4, x0
fdiv.s f4, f1, f2 
li a0, -9
li a1, 2
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f5, x0
fdiv.s f5, f1, f2 
li a0, -5
li a1, -9
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f6, x0
fdiv.s f6, f1, f2 
li a0, 33333
li a1, 0
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f7, x0
fdiv.s f7, f1, f2 
jr ra
