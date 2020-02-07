# Your name/date
# Appropriate documentation

# insert your terms procedure and your Polish function here

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
