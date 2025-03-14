li a0, 5
li a1, 4
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f3, x0
fsub.s f3, f1, f2
li a0, 5
li a1, -4
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f4, x0
fsub.s f4, f1, f2
li a0, -5
li a1, 4
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f5, x0
fsub.s f5, f1, f2
li a0, -8
li a1, -10
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f6, x0
fsub.s f6, f1, f2
li a0, 66
li a1, 0
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f7, x0
fsub.s f7, f1, f2
jr ra
