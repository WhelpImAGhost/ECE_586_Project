li a0, 55
fcvt.s.w f1, a0
li s2, 0
fmv.x.w s2, f1
li a0, 55
li a1, 10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fdiv.s f3, f1, f2
li s3, 0
fmv.x.w s3, f3
li a0, -55
fcvt.s.w f1, a0
li s4, 0
fmv.x.w s4, f1
li a0, 55
li a1, -10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fdiv.s f3, f1, f2
li s5, 0
fmv.x.w s5, f3
li a0, 0
fcvt.s.w f1, a0
li s6, 2025
fmv.x.w s6, f1
jr ra
