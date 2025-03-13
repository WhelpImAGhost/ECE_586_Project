li a0, 0x00000000
li a1, 12
li s2, 0xFFFFFFFF
sll s2, a0, a1
li a0, 0xFFFFFFFF
li a1, 12
li s3, 0x00000000
sll s3, a0, a1
li a0, 0xF0F0F0F0
li a1, 16
li s4, 0xFFFFFFFF
sll s4, a0, a1
li a0, 0xFFFFFFFF
li a1, 32
li s5, 0xFFFFFFFF
sll s5, a0, a1
jr ra
