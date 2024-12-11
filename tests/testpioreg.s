	.file	"testpioreg.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	PIO_REG_ADDR
	.section	.sdata,"aw"
	.align	3
	.type	PIO_REG_ADDR, @object
	.size	PIO_REG_ADDR, 8
PIO_REG_ADDR:
	.dword	536870912
	.section	.rodata
	.align	3
.LC0:
	.string	"Wrote 0x12345678 to PioReg at 0x20000000"
	.align	3
.LC1:
	.string	"Read 0x%08x from PioReg\n"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	lui	a5,%hi(PIO_REG_ADDR)
	ld	a5,%lo(PIO_REG_ADDR)(a5)
	li	a4,305418240
	addi	a4,a4,1656
	sw	a4,0(a5)
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	puts
	lui	a5,%hi(PIO_REG_ADDR)
	ld	a5,%lo(PIO_REG_ADDR)(a5)
	lw	a5,0(a5)
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	mv	a1,a5
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	printf
	li	a5,0
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (g04696df0963) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
