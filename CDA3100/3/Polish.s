# Jon Crawford 2/10/2018
# polish.s a program to return the first 16 polish values to console
# terms function uses t0-t2 to process the given value from main and loop
# polish function uses t3-t5 to process the value given from terms and loop
# polish uses modulo from discrete math 1 to separate value from its remainder
# when dividing by 10 creates and perfect split in the integer

terms:
	addi 	$sp, $sp, -16		# Allocate
	sw 	$ra, 0($sp)
	sw 	$t0, 4($sp)
	sw 	$t1, 8($sp)
	sw 	$t2, 12($sp)
	
	move $t0, $a0 			# move n to print msg
	
	la	$a0, msg		# print first 16 terms msg
	li	$v0, 4
	syscall
	
	move 	$a0, $t0 		# print term
	li	$v0, 1
	syscall	
	
	li 	$a0, 32 		# 32 = ascii space
	li	$v0, 11
	syscall
	
	li 	$t1, 0 			# int index = 0 
	li 	$t2, 15 		# int max = 15
	
	termsLoop:  
	
		ble  	$t2, $t1, termsExit 	# while (index <= max)
		move 	$a0, $t0		# Bring back n	
		
		jal polish			# moved in n and call polish
	
		move 	$t0, $v0		# Save polish return value
	
		move 	$a0, $t0 		# Move return value into print
		li	$v0, 1			# Print Value
		syscall
	
		li 	$a0, 32			# 32 = ascii space
		li 	$v0, 11
		syscall
	
		move 	$a0, $t0		# Move in new n value 
	
		addi 	$t1, $t1, 1		# index++
		
		j    termsLoop            	# loop 
	
termsExit:
	
	lw 	$ra, 0($sp)		# Restore
	lw 	$t0, 4($sp)
	lw 	$t1, 8($sp)
	lw 	$t2, 12($sp)
	addi 	$sp, $sp, 16
	
	jr 	$ra	

	polish:
	
		addi 	$sp, $sp, -16		# Allocation
		sw 	$ra, 0($sp)
		sw 	$t3, 4($sp)
		sw 	$t4, 8($sp)			  
		sw 	$t5, 12($sp)			 
	
		polishLoop:
		
			ble  	$a0, $0, polExit	# Loop Sentinel
			move 	$t3, $a0		# save n
			 
			div 	$a0, $t3, 10		# t3 / 10
			rem 	$t4, $t3, 10		# t3 mod 10
		
			mul 	$t4, $t4, $t4 		# t4^2
			add 	$t5, $t5, $t4 		# add values
			
			j polishLoop
	
	polExit:
		move 	$v0, $t5 		# Return polish value
		
		lw 	$ra, 0($sp)		# Restore
		lw 	$t3, 4($sp)
		lw 	$t4, 8($sp)
		lw 	$t5, 12($sp)
		addi 	$sp, $sp, 16
	
		jr 	$ra	
	
	
# Driver program provided by Stephen P. Leach -- written 11/12/17

main:	la	$a0, intro	# print intro
	li	$v0, 4
	syscall

loop:	la	$a0, req	# request value of n
	li	$v0, 4
	syscall

	li	$v0, 5		# read value of n
	syscall

	ble	$v0, $zero, out	# if n is not positive, exit

	move	$a0, $v0	# set parameter for terms procedure

	jal	terms		# call terms procedure

	j	loop		# branch back for next value of n

out:	la	$a0, adios	# display closing
	li	$v0, 4
	syscall

	li	$v0, 10		# exit from the program
	syscall

	.data
intro:	.asciiz	"Welcome to the Polish sequence tester!"
req:	.asciiz	"\nEnter an integer (zero or negative to exit): "
adios:	.asciiz	"Come back soon!\n"
msg:	.asciiz "First 16 terms: "