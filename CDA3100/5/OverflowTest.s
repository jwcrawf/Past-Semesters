# Stephen P. Leach -- 03/25/18
# OverflowTest.s - a simple program that tests for overflow.  User enters integer values  
#	for x and y.  If x is zero, the program terminates.  Otherwise, the program
#	determines if computing the value x+y will produce an overflow.  If not, the 
#	proper sum is displayed; if so, an overflow message is produced and the 
#	"incorrect" value is displayed.  In either case, the program then loops back for
#	two more values of x and y.
# Register use:
#	$a0	parameter for syscall
#	$v0	syscall parameter (and return value)
#	$t0	x+y
#	$t1	x
#	$t2	y
#	$t3	temporary use

main:	la	$a0, intro		# print intro
	li	$v0, 4
	syscall

loop:	la	$a0, xreq		# request value of x
	li	$v0, 4
	syscall

	li	$v0, 5			# get value of x
	syscall

	beq	$v0, $zero, out		# exit if x = 0
	move	$t1, $v0		# otherwise, place x in $t1

	la	$a0, yreq		# request value of y
	li	$v0, 4
	syscall

	li	$v0, 5			# get value of y
	syscall

	move	$t2, $v0		# place y in $t2

	addu	$t0, $t1, $t2		# these 7 lines are nearly verbatim from top of page 182
	xor	$t3, $t1, $t2
	slt	$t3, $t3, $zero
	bne	$t3, $zero, ok
	xor	$t3, $t0, $t1
	slt	$t3, $t3, $zero
	beq	$t3, $zero, ok

	la	$a0, bad		# if we fall through to this code, there was overflow
	li	$v0, 4
	syscall

	move	$a0, $t0		# display "incorrect" value
	li	$v0, 1
	syscall

	j	loop			# and loop back for next values of x and y

ok:	la	$a0, good		# no overflow; display correct sum
	li	$v0, 4
	syscall

	move	$a0, $t0
	li	$v0, 1
	syscall

	j	loop			# and loop back for next values of x and y
	
out:	li	$v0, 10			# exit from the program
	syscall

	.data
intro:	.asciiz	"Testing for overflow ..."
xreq:	.asciiz	"\nEnter value of x (0 to exit): "
yreq:	.asciiz	"Enter value of y: "
bad:	.asciiz	"Overflow!  Incorrect value: "
good:	.asciiz "x + y = "
