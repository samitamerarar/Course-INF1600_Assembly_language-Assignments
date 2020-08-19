.global matrix_column_aver_asm

matrix_column_aver_asm:
		push %ebp                      /* Save old base pointer */
		mov %esp, %ebp                 /* Set ebp to current esp */
		subl $12, %esp
		movl $0, -4(%ebp)              /* r = 0 */
		movl $0, -8(%ebp)              /* c = 0 */
		movl $0, -12(%ebp)             /* elem = 0 */
		
	boucle1:
		movl -8(%ebp), %eax
		cmp 16(%ebp), %eax             /* Compare matorder et c */
		jae fin 
		movl $0, -12(%ebp)             /* elem = 0 */		
		
	boucle2:
		movl -4(%ebp), %eax
		cmp 16(%ebp), %eax             /* Compare matorder et r */
		jl situation1

		movl $0, -4(%ebp)              /* r = 0 */
		jmp suite
		
	situation1:
		
		movl 16(%ebp), %eax            /* indice de inmatdata */
		imull -4(%ebp), %eax
		addl -8(%ebp), %eax            /* c+r*matorder */
		
		movl 8(%ebp), %ebx             /* inmatdata */
		movl (%ebx, %eax, 4), %ebx
		
		addl %ebx, -12(%ebp)           /* elem += inmatdata[c+r*matorder] */
		incl -4(%ebp)                  /* r++ */
		jmp boucle2
		
	suite:
		xor %edx, %edx
		xor %eax, %eax
		movl 16(%ebp), %ebx            /* matorder */
		movl -12(%ebp), %eax           /* elem */
		divl %ebx                      /* elem/matorder */
		
		movl -8(%ebp), %ecx            /* c, indice de outmatdata */
		movl 12(%ebp), %edi
		movl %eax, (%edi, %ecx, 4)     /* outmatdata[c] = elem/matorder */
		
		incl -8(%ebp)                  /* c++ */
		jmp boucle1

	fin:
		addl $12, %esp	
		leave                          /* Restore ebp and esp */
		ret                            /* Return to the caller */
