sort:	addi	$sp, $sp, -20	# save $ra and $s0-$s3
	sw	$ra, 16($sp)	# on stack
	sw	$s3, 12($sp)
	sw	$s2, 8($sp)
	sw	$s1, 4($sp)
	sw	$s0, 0($sp)

	move	$s2, $a0		# keep sort's parameters
	move	$s3, $a1		# in $s2 and $s3

	li	$s0, 1		# outer loop (i)
for1:	slt	$t0, $s0, $s3
	beq	$t0, $zero, exit1

	addi	$s1, $s0, -1	# inner loop (j)
for2:	slti	$t0, $s1, 0
	bne	$t0, $zero, exit2
	sll	$t1, $s1, 2
	add	$t2, $s2, $t1
	lw	$t3, 0($t2)	# load v[j] and v[j+1]
	lw	$t4, 4($t2)
	slt	$t0, $t4, $t3
	beq	$t0, $zero, exit2	# see if swap is needed

	move	$a0, $s2		# if so, perform swap
	move	$a1, $s1
	jal	swap

	addi	$s1, $s1, -1	# decrement j (inner loop)
	j	for2

exit2:	addi	$s0, $s0, 1		# increment i (outer loop)
	j	for1

exit1:	lw	$s0, 0($sp)	# restore values from stack
	lw	$s1, 4($sp)
	lw	$s2, 8($sp)
	lw	$s3, 12($sp)
	lw	$ra, 16($sp)
	addi	$sp, $sp, 20

	jr	$ra		# return to calling routine
	
swap:	sll	$t1, $a1, 2		# compute address of v[k]
	add	$t1, $a0, $t1

	lw	$t0, 0($t1)	# load v[k]
	lw	$t2, 4($t1)	# load v[k+1]

	sw	$t2, 0($t1)	# swap values
	sw	$t0, 4($t1)

	jr	$ra		# return to calling routine

main:	la	$a0, text1		# display original values in array
	li	$v0, 4
	syscall

	la	$a0, array		# call sort procedure
	li	$a1, 10
	jal	sort

	la	$a0, text2		# display sorted values
	li	$v0, 4
	syscall

	la	$t0, array		# base address of array
	li	$t1, 10		# number of values

loop:	beq	$t1, $zero, done	# print numbers one at a time

	lw	$a0, 0($t0)	# actual value
	li	$v0, 1
	syscall

	la	$a0, blank		# print a space after each number 
	li	$v0, 4
	syscall

	addi	$t0, $t0, 4		# load next value
	addi	$t1, $t1, -1	# decrement counter
	j	loop

done:	la	$a0, cr		# print a newline
	li	$v0, 4
	syscall

	li	$v0, 10		# exit
	syscall

	.data
array:	.word	100, -2, 19, 211, -80, 0, 16, 923, 19, 301
text1:	.asciiz	"Testing sort with 100 -2 19 211 -80 0 16 923 19 301\n"
text2:	.asciiz	"\nValues after sort: "
blank:	.asciiz	" "
cr:	.asciiz "\n"