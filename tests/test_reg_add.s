	.file	"test_reg_add.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0_v1p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC2:
	.string	"Result: "
	.align	3
.LC3:
	.string	"%d "
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	lui	a5,%hi(.LANCHOR0)
	addi	a5,a5,%lo(.LANCHOR0)
	ld	a2,0(a5)
	ld	a3,8(a5)
	ld	a4,16(a5)
	vsetivli	zero,8,e8,mf2,ta,ma
	ld	a5,24(a5)
	vmv.v.i	v1,0
	addi	sp,sp,-80
	sd	ra,72(sp)
	sd	s0,64(sp)
	sd	s1,56(sp)
	sd	a5,24(sp)
	addi	a5,sp,40
	vse8.v	v1,0(a5)
	addi	a5,sp,32
	sd	a2,0(sp)
	sd	a3,8(sp)
	sd	a4,16(sp)
	vse8.v	v1,0(a5)
	li	a4,8
	addi	a3,sp,16
	addi	a2,sp,32
 #APP
# 11 "test_reg_add.c" 1
	vsetvli t0, sp, e32, m1
vle32_v v0, a3
vle32_v v1, a2
vadd.vv v2, v0, v1
vse32_v v2, a4

# 0 "" 2
 #NO_APP
	lui	a0,%hi(.LC2)
	addi	a0,a0,%lo(.LC2)
	call	printf
	addi	s0,sp,32
	lui	s1,%hi(.LC3)
.L2:
	lh	a1,0(s0)
	addi	a0,s1,%lo(.LC3)
	addi	s0,s0,2
	call	printf
	addi	a5,sp,48
	bne	s0,a5,.L2
	li	a0,10
	call	putchar
	ld	ra,72(sp)
	ld	s0,64(sp)
	ld	s1,56(sp)
	li	a0,0
	addi	sp,sp,80
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	3
	.set	.LANCHOR0,. + 0
.LC0:
	.half	1
	.half	2
	.half	3
	.half	4
	.half	5
	.half	6
	.half	7
	.half	8
.LC1:
	.half	8
	.half	7
	.half	6
	.half	5
	.half	4
	.half	3
	.half	2
	.half	1
	.ident	"GCC: (g04696df0963) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
