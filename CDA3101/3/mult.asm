	addiu $t1,$zero,0x0005
	addiu $t2,$zero,0x0002
  mult $t2,$t1
  mflo $a0
  addiu	$v0,$zero,1		# print a0
	syscall
	addiu	$v0,$zero,10		# exit
	syscall
	
