# Jon Crawford 1/20/2018
# fact.s - program to return a factorial
# Register use:
# $a0-$a3 parameters for fact and syscall
# $v0 syscall parameter
# $t0-$t1 temporary calculations
# $s0 the value from fact

fact:	slti	$t0, $a0, 1	# test for n < 1
	beq	$t0, $zero, L1	# if n >= 1, go to L1

	li	$v0, 1		# return 1
	jr	$ra		# return to instruction after jal

L1:	addi	$sp, $sp, -8	# adjust stack for 2 items
	sw	$ra, 4($sp)	# save the return address
	sw	$a0, 0($sp)	# save the argument n

	addi	$a0, $a0, -1	# n >= 1; argument gets (n – 1)
	jal	fact		# call fact with (n – 1)

	lw	$a0, 0($sp)	# return from jal: restore argument n
	lw	$ra, 4($sp)	# restore the return address
	addi	$sp, $sp, 8	# adjust stack pointer to pop 2 items

	mul	$v0, $a0, $v0	# return n * fact (n – 1)

	jr	$ra		# return to the caller


main:	la	$a0, intro	# Print intro msg
	li	$v0, 4
	syscall

loop:	la 	$a0, inval	# Prompt user for value
	li 	$v0, 4
	syscall

	li 	$v0, 5		# Read in value from user
	syscall
	move 	$a0, $v0	# Move invalue into $a0
	
	slti	$t1, $a0, 0	# Check for Sentinel & quit
	bne	$t1, $zero, quit
		
	li	$v0, 1		# Print value before answer msg
	syscall

	jal fact		# Function call

	move	$s0, $v0	# Store value from function
	
	la	$a0, answer	# Print answer msg
	li	$v0, 4
	syscall

	move	$a0, $s0	# Print factorial value
	li	$v0, 1
	syscall
		
	j loop			# Loop to prompt

quit:	la	$a0, end	# Print goodbye msg	
	li	$v0, 4
	syscall

	li	$v0, 10		# Exit program		
	syscall

	.data
intro: 	.asciiz "Welcome to the factorial tester!"
inval: 	.asciiz "\nEnter a value for n (or a negative value to exit): "
answer:	.asciiz "! is "
end: 	.asciiz "Come back soon!"