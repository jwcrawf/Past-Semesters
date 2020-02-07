# Stephen P. Leach -- 03/10/12
# Example Problem.s - functions that produce the sum m+(m+1)+..+n   
#	The integer values of m and n are input by the user.  
#	If n < m, output the value 0.

##
## 	Your code for Summit and Formula could go here
##


# Driver program provided by Stephen P. Leach -- written 03/10/12
# Register use:
#	$s0	the value of m
#	$s1	the value of n
#	$s2	the value of the sum [m+(m+1)+..+n]

main:	la	$a0, intr		# print intro
	li	$v0, 4
	syscall

next:	la	$a0, reqm		# request value of m
	li	$v0, 4
	syscall

	li	$v0, 5			# read value of m
	syscall

	ble	$v0, $zero, out		# if m is 0 or negative, exit

	move	$s0, $v0		# save value of m in $s0

	la	$a0, reqn		# request value of n
	li	$v0, 4
	syscall

	li	$v0, 5			# read value of n
	syscall

	move	$s1, $v0		# save value of n

	move	$a0, $s0		# set parameter m for Summit function
	move	$a1, $v0		# set parameter n for Summit function

	jal	Summit			# invoke Summit function

	move	$s2, $v0		# save answer

	la	$a0, txt1		# display answer (txt1)
	li	$v0, 4
	syscall

	move	$a0, $s0		# display m
	li	$v0, 1
	syscall

	la	$a0, txt2		# display answer (txt2)
	li	$v0, 4
	syscall

	move	$a0, $s1		# display n
	li	$v0, 1
	syscall

	la	$a0, txt3		# display answer (txt3)
	li	$v0, 4
	syscall

	move	$a0, $s2		# display answer (value)
	li	$v0, 1
	syscall

	j	next			# branch back for next value of m

out:	la	$a0, done		# display closing
	li	$v0, 4
	syscall

	li	$v0, 10		# exit from the program
	syscall


	.data
intr:	.asciiz  "Welcome to the Example Problem tester!"
reqm:	.asciiz  "\nEnter a value for m (0 or negative to exit): "
reqn:	.asciiz  "Enter a value for n: "
txt1:	.asciiz  "The sum of the numbers from "
txt2:	.asciiz  " to "
txt3:	.asciiz  " is "
done:	.asciiz  "Come back soon!\n"

