strcpy:	lb  	$t1, 0($a1)  	  		
	sb  	$t1, 0($a0)  	            
	beq	$t1, $zero, L1 
	addi 	$a0, $a0, 1  	  
	addi 	$a1, $a1, 1  	  
	j  strcpy 

L1:   	jr  $ra 
 
