.global _start
_start:

lla     a5, .LC0
        lw      s2,0(a5)
        lw      s3,4(a5)
	jr	ra
.section .data
.LC0:
	.word 0x11223344
	.word 0x44332211


