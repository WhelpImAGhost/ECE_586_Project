li a0, 2
li a1, 2
li a2, 2
fcvt.s.wu f1, a0
fcvt.s.wu f2, a1
fcvt.s.wu f3, a2
fcvt.s.wu f4, x0
fmsub.s f4, f1, f2, f3
li a0, 2
li a1, 2
li a2, -2
fcvt.s.wu f1, a0
fcvt.s.wu f2, a1
fcvt.s.w f3, a2
fcvt.s.wu f5, x0
fmsub.s f5, f1, f2, f3
li a0, 4
li a1, -4
li a2, -4
fcvt.s.wu f1, a0
fcvt.s.w f2, a1
fcvt.s.w f3, a2
fcvt.s.wu f6, x0
fmsub.s f6, f1, f2, f3
li a0, 4
li a1, -4
li a2, 4
fcvt.s.wu f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f3, a2
fcvt.s.wu f7, x0
fmsub.s f7, f1, f2, f3
li a0, -4
li a1, 4
li a2, -4
fcvt.s.w f1, a0
fcvt.s.wu f2, a1
fcvt.s.w f3, a2
fcvt.s.wu f8, x0
fmsub.s f8, f1, f2, f3
li a0, -4
li a1, 4
li a2, 4
fcvt.s.w f1, a0
fcvt.s.wu f2, a1
fcvt.s.wu f3, a2
fcvt.s.wu f9, x0
fmsub.s f9, f1, f2, f3
li a0, -2
li a1, -2
li a2, -2
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.w f3, a2
fcvt.s.wu f10, x0
fmsub.s f10, f1, f2, f3
li a0, -2
li a1, -2
li a2, 2
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.wu f3, a2
fcvt.s.wu f11, x0
fmsub.s f11, f1, f2, f3
li a0, 0
li a1, 5
li a2, 2
fcvt.s.wu f1, a0
fcvt.s.wu f2, a1
fcvt.s.wu f3, a2
fcvt.s.wu f12, x0
fmsub.s f12, f1, f2, f3
li a0, 6
li a1, 0
li a2, -68
fcvt.s.wu f1, a0
fcvt.s.wu f2, a1
fcvt.s.w f3, a2
fcvt.s.wu f13, x0
fmsub.s f13, f1, f2, f3
li a0, 0
li a1, 12
li a2, 0
fcvt.s.wu f1, a0
fcvt.s.wu f2, a1
fcvt.s.wu f3, a2
fcvt.s.wu f14, x0
fmsub.s f14, f1, f2, f3
jr ra
