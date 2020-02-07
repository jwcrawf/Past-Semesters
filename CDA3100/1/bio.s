# Jonathan Crawford -- 01/22/18
# bio.s -- an introductory bio program
# Register use:
# 	$v0 	syscall parameter and return value
# 	$a0 	syscall parameter
	.text
	.globl main
main:
	la 	$a0, msg1	# address of my name message
	li 	$v0, 4 		# this is the print_string option
	syscall 		# perform the system call
	
	la 	$a0, msg2
	li 	$v0, 4 		# this is the print_string option
	syscall 		# perform the system call
	
	la 	$a0, msg3
	li 	$v0, 4 		# this is the print_string option
	syscall 		# perform the system call
	
	la 	$a0, msg4
	li 	$v0, 4 		# this is the print_string option
	syscall 		# perform the system call
	
	li 	$v0, 10 	# this is the exit option
	syscall 		# perform the system call
# Here is the data for the program
	.data
msg1: .asciiz 	"My name is Jon Crawford\n"
msg2: .asciiz	"I was born in Medina, Ohio, but grew up outside Detroit, Michigan\n"
msg3: .asciiz	"I am a factory design consultant who dreams of becoming a robotics engineer\n"
msg4: .asciiz	"I enjoy hiking with my schnauzer Ted, cooking bbq, and watching european soccer"
# end bio.s
