# Jon Crawford -- 4/23/18
# exp.s - A simple program to approximate e in double precision  
#	      
#
# Register use:
#	$a0	parameter for syscall
#	$v0	syscall parameter 
#	$f0	float syscall return value
#	$f12	float syscall parameter	
#	$f14-16 constant values
#	$f4-f22 all calculation variables are declared inline
	
exp:	l.d 	$f14, conE		# double E
	l.d	$f16, con0		# double 0.0
	l.d	$f10, con1      	# double 1.0
	l.d	$f6,  con0		# double sum = 0
	l.d	$f4,  con1		# double n = 1
	
	mov.d 	$f18, $f12		# copy of invalue
	mov.d	$f20, $f18	 

	abs.d	$f20, $f20		# abs(x);
	
	div.d	$f22, $f20, $f4 	# z = x/n;		
	add.d	$f6, $f10, $f20		# sum = 1 + x;
	
		
	calc:	add.d	$f4, $f4, $f10		# ++n;
		
		div.d	$f22, $f22, $f4		# z = z/n;
		
		mul.d	$f22, $f22, $f20	# z*=x;
		
		
		c.lt.d  $f22, $f14 		# if (val < E)
		bc1t 	done			#   break;
	
		add.d	$f6, $f6, $f22		# sum += val;
		
		j	calc			# loop for next sum
	
done:	c.lt.d  $f18, $f16		# if (!copy of x < 0) skip;
	bc1f	skip
	
	div.d 	$f6, $f10, $f6		# else, x = 1/x;
	
	
skip:	mov.d	$f0, $f6
	jr 	$ra		# return to caller


main:	la	$a0, intro	# print intro msg
	li	$v0, 4
	syscall
	
loop:	la	$a0, inval	# prompt user
	li	$v0, 4
	syscall

	li	$v0, 7		# read value
	syscall
			
	l.d 	$f14, nines
	c.eq.d 	$f0, $f14
	bc1t 	exit		# branch on nines
	
	mov.d 	$f8, $f0	# save inval to print
	mov.d 	$f12, $f0	
	
	jal exp			# call e^x function
	
	mov.d	$f2, $f0 	# save e^x return value
	
	la	$a0, emsg	# print e^ msg
	li	$v0, 4
	syscall
	
	mov.d	$f12, $f8		
	li	$v0, 3		# print invalue
	syscall
	
	la	$a0, ismsg	# print is 
	li	$v0, 4
	syscall
	
	mov.d	$f12, $f2 	# print e^x value
	li	$v0, 3		
	syscall
	
	j	loop		# loop

exit:	la	$a0, end	# print end msg
	li	$v0, 4
	syscall

	li	$v0, 10		# exit program
	syscall

	
	.data
intro:	.asciiz  "Let's test our exponential function!"
inval:	.asciiz  "\nEnter a value for x (or 999 to exit): "
emsg:	.asciiz  "Our approximation for e^"
ismsg:	.asciiz  " is "
end:	.asciiz  "Come back soon!\n"
nines:	.double  999.0
con1:   .double  1.0
con0:   .double  0.0
conE:   .double  0.000000000000001
