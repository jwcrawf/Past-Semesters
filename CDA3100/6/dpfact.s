# Jon Crawford -- 4/21/18
# dpfact.s - A simple addition to our factorial program to 
# 	     return a double precision factorial value.

# Register use:
#	$a0	parameter for syscall
#	$v0	syscall parameter 
#	$f12	float return value
#	$f0	float syscall parameter	
#	$f2	used for n
#	$t0	temporary use for calculation
#	$t1	index count

dpfact:	li	$t0, 1			# initialize product to 1.0
	mtc1	$t0, $f0
	cvt.d.w	$f0, $f0

again:	slti	$t0, $a0, 2		# test for n < 2
	bne	$t0, $zero,done		# if n < 2, return

	mtc1	$a0, $f2		# move n to floating register
	cvt.d.w	$f2, $f2		# and convert to double precision

	mul.d	$f0, $f0, $f2		# multiply product by n
	
	addi	$a0, $a0, -1		# decrease n
	j	again			# and loop

done:	jr	$ra			# return to calling routine
 
 
main:	la	$a0, intro	        # Print intro msg
	li	$v0, 4
	syscall

loop:	la 	$a0, inval	        # Prompt user for value
	li 	$v0, 4
	syscall

	li 	$v0, 5		        # Read in value from user
	syscall
	move 	$a0, $v0	        # Move invalue into $a0
	
	slti	$t1, $a0, 0	        # Check for Sentinel & quit
	bne	$t1, $zero, quit
		
	li	$v0, 1		        # Print value before answer msg
	syscall

	jal dpfact		        # Function call

		
	la	$a0, answer	        # Print answer msg
	li	$v0, 4
	syscall

	mov.d	$f12, $f0	        # Print factorial value
	li	$v0, 3      
	syscall
		
	j loop			        # Loop to prompt

quit:	la	$a0, end	        # Print goodbye msg	
	li	$v0, 4
	syscall

	li	$v0, 10		        # Exit program		
	syscall

	.data
intro: 	.asciiz "Welcome to the factorial tester!"
inval: 	.asciiz "\nEnter a value for n (or a negative value to exit): "
answer:	.asciiz "! is "
end: 	.asciiz "Come back soon!"
