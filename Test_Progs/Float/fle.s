li a0, -10
li a1, -10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fle.s s2, f1, f2
li a0, 10
li a1, -10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fle.s s3, f1, f2
li a0, -10
li a1, 10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fle.s s4, f1, f2
li a0, 10
li a1, -10
li a2, 0
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.w f4, a2
fdiv.s f1, f1, f4
fle.s s5, f1, f2
jr ra
