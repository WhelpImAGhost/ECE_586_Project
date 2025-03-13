li a0, 0x7FFFFFFF
li a1, 0x10
mulh s2, a0, a1
li a0, 0x7FFFFFFF
li a1, 0xFFFFFFF0
mulh s3, a0, a1
li a0, 0x80000001
li a1, 0x10
mulh s4, a0, a1
li a0, -1
li a1, -1
mulh s5, a0, a1
li a0, 0xFFFFFFFF
li a1, 0
mulh s6, a0, a1
jr ra
