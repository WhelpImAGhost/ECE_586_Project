li a0, 25000
li a1, 3500
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f3, x0
fmin.s f3, f1, f2
li a0, 5767
li a1, 5777
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f4, x0
fmin.s f4, f1, f2
li a0, 1
li a1, -200
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f5, x0
fmin.s f5, f1, f2
li a0, -86000
li a1, 8323
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f6, x0
fmin.s f6, f1, f2
li a0, -1
li a1, -5
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f7, x0
fmin.s f7, f1, f2
li a0, -50320
li a1, -542
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f8, x0
fmin.s f8, f1, f2
li a0, 0
li a1, 100
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f9, x0
fmin.s f9, f1, f2
li a0, 0
li a1, -100
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f10, x0
fmin.s f10, f1, f2
jr ra
