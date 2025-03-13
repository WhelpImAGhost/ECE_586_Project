li a0, -10
li a1, -10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
feq.s s2, f1, f2
li a0, 10
li a1, -10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
feq.s s3, f1, f2
li a0, -10
li a1, 10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
feq.s s4, f1, f2
li a0, 10
li a1, -10
li a2, 0
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.w f14, a2
fdiv.s f1, f1, f14
feq.s s5, f1, f2
jr ra
