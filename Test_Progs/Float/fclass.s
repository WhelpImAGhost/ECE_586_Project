li a0, 10
li a1, 0
li a2, -1
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fcvt.s.w f3, a2
fdiv.s f1, f1, f2
fmul.s f1, f1, f3
fclass.s s2, f1
li a0, -10
fcvt.s.w f1, a0
fclass.s s3, f1
li a0, 2147483649
fmv.w.x f1, a0
fclass.s s4, f1
li a0, 0
li a1, -1
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fmul.s f1, f1, f2
fclass.s s5, f1
li a0, 0
li a1, 1
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fmul.s f1, f1, f2
fclass.s s6, f1
li a0, 1
fmv.w.x f1, a0
fclass.s s7, f1
li a0, 10
fcvt.s.w f1, a0
fclass.s s8, f1
li a0, 10
li a1, 0
fcvt.s.w f1, a0
fcvt.s.w f2, a1
fdiv.s f1, f1, f2
fclass.s s9, f1
li a0, -1
fcvt.s.w f1, a0
fsqrt.s f1, f1
fclass.s s10, f1
li a0, 0
fcvt.s.w f1, a0
fdiv.s f1, f1, f1
fclass.s s11, f1
jr ra
