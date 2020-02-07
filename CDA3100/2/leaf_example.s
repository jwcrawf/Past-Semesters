# Stephen P. Leach – 09/16/15 
# leaf_example.s – a simple driver program that tests the first
#	example in the text
# Register use:
#	$a0-$a3	parameters for leaf_example and syscall
#	$v0	syscall parameter
#	$t0-$t1	temporary calculations
#	$s0	the variable f

leaf_example:
	addi	$sp, $sp, -4	# adjust stack to make room for 1 item
	sw	$s0, 0($sp)	# save register $s0 for use afterwards

	add	$t0, $a0, $a1	# register $t0 contains g + h
	add	$t1, $a2, $a3	# register $t1 contains i + j
	sub	$s0, $t0, $t1	# f = $t0 - $t1, which is (g + h) – (i + j)
	add	$v0, $s0, $zero	# returns f ($v0 = $s0 + 0)

	lw	$s0, 0($sp)	# restore register $s0 for caller
	addi	$sp, $sp, 4	# adjust stack to delete 1 item

	jr	$ra		# jump back to calling routine

main:
	la	$a0, greq		# request value of g
	li	$v0, 4
	syscall

	li	$v0, 5		# read value of g
	syscall
	move	$s0, $v0		# save value of g in $s0

	la	$a0, hreq		# request value of h
	li	$v0, 4
	syscall

	li	$v0, 5		# read value of h
	syscall
	move	$a1, $v0		# place value of h in $a1

	la	$a0, ireq		# request value of i
	li	$v0, 4
	syscall

	li	$v0, 5		# read value of i
	syscall
	move	$a2, $v0		# place value of i in $a2 

	la	$a0, jreq		# request value of j
	li	$v0, 4
	syscall

	li	$v0, 5		# read value of j
	syscall
	move	$a3, $v0		# place value of j in $a3

	move	$a0, $s0		# move value of g into $a0

	jal	leaf_example	# invoke leaf_example procedure

	move	$s0, $v0		# save value returned by leaf_example

	la	$a0, ans		# display answer (text)
	li	$v0, 4
	syscall
	
	move	$a0, $s0		# move result into $a0
	li	$v0, 1		# display answer (integer)
	syscall

	la	$a0, cr		# display closing
	li	$v0, 4
	syscall

	li	$v0, 10		# exit from the program
	syscall

	.data
greq:	.asciiz	"What is the value of g? "
hreq:	.asciiz	"What is the value of h? "
ireq:	.asciiz	"What is the value of i? "
jreq:	.asciiz	"What is the value of j? "
ans:	.asciiz	"The value returned by leaf_example is "
cr:	.asciiz	"\nThanks for testing my code!\n"
