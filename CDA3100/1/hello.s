# Jonathan Crawford -- 01/22/18
# hello.s -- an introductory program
# Register use:
# 	$v0 	syscall parameter and return value
# 	$a0 	syscall parameter
	
	.globl main
main:
	la 	$a0, msg1	# address of my name message
	
	li 	$v0, 4 		# this is the print_string option
	syscall 		# perform the system call
	li 	$v0, 10 	# this is the exit option
	syscall 		# perform the system call
# Here is the data for the program
	.data
msg1: .asciiz 	"Hello World\n"
# end hello.s