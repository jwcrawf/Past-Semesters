# Jon Crawford -- 4/2/18
# altfib.s - A simple program to print the alternating positive and negative value from the fibonacci 		#	sequence, print the values 5 per line, while testing for overflow of the next value, printing 
#	the offending overflow value on the screen and terminating the sequence.

# Register use:
#	$a0	parameter for syscall
#	$v0	syscall parameter 
#	$s0-1	used for n, n-1 of sequence
#	$s2-3	used for loop index range [0,1,2,3,4]	
#	$t0-2	temporary use for calculation



main:	la	$a0, intro		# print intro msg
	
	li	$v0, 4
	syscall



	li	$s2, 0			# int index = 0;
	
	li	$s3, 4			# int max = 4;

   					 

	li	$s0, 0			# int n-1 = 0;
	
	li	$s1, 1			# int n = 1;

	
loop:	move 	$a0, $s1		# print n value
	
	li 	$v0, 1
	
	syscall
	
	
	
	li	$a0, 32			# print ASCII Space
	
	li	$v0, 11
	
	syscall
	
	
	
	negu	$t1, $s1		# get n opposite 	
	
	
	addu	$t0, $s0, $t1		# get altfib value
	
	xor	$t2, $s0, $t1	 
	
# check signs	
	slt	$t2, $t2, $zero	 
	
	bne 	$t2, $zero, ok	
	# signs pass, continue
	xor	$t2, $t0, $s0	  
	# check altfib sign
	slt	$t2, $t2, $zero	 
	
	bne	$t2, $zero, bad

 	# signs fail, overflow

ok:	move	$s0, $s1		# move n into n-1	
	move 	$s1, $t0	
	
# save altfib to n 	
	
	addi	$s2, $s2, 1		# ++index;
			
	blt 	$s3, $s2, car		# if (index == max ) "\n"
	
	j loop





car:	la	$a0, cr			# carriage return
	
	li	$v0, 4	
	
	
	
	li	$s2, 0			# int index = 0;
	
	syscall	
	
	
	j loop





bad:	la	$a0, overflow		# print overflow msg
	
	li	$v0, 4
	
	syscall

	
	
	move	$a0, $t0		# print overflow value
	
	li	$v0, 1
	
	syscall
	

exit:	li	$v0, 10			# exit
	
	syscall


	

	.data

intro:		.asciiz "Here are the alternating Fibonacci numbers that I produced:\n\n"
cr:		.asciiz "\n"

overflow:	.asciiz "\n\nValue causing overflow = "