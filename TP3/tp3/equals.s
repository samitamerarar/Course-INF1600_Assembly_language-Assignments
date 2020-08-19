.globl matrix_equals_asm

matrix_equals_asm:
		push %ebp                       /* Save old base pointer */
		mov %esp, %ebp                  /* Set ebp to current esp */
		subl $8, %esp
		movl $0, -4(%ebp)               /* r = 0 */
		movl $0, -8(%ebp)               /* c = 0 */
		
	boucle1:
		movl -4(%ebp), %eax
		cmpl 16(%ebp), %eax             /* Compare matorder et r */
		jae return1
	
	boucle2:
		movl -8(%ebp), %eax
		cmpl 16(%ebp), %eax             /* Compare matorder et c */
		jl condition

		incl -4(%ebp)                   /* r++ */
		jmp boucle1			

	condition:
		movl 16(%ebp), %eax             /* indice de inmatdata1 et inmatdata2 */
		imull -4(%ebp), %eax		
		addl -8(%ebp), %eax             /* c+r*matorder */
			
		movl 8(%ebp), %ebx              /* pointeur au debut du tableau inmatdata1 */
		movl (%ebx, %eax, 4), %ebx      /* l'élément à [c+r*matorder] de inmatdata1 */
		movl 12(%ebp), %ecx             /* pointeur au debut du tableau inmatdata2 */
		movl (%ecx, %eax, 4), %ecx      /* l'élément à [c+r*matorder] de inmatdata2 */		

		cmpl %ebx, %ecx                 /* Compare les deux éléments */
		jne return0			
		incl -8(%ebp)                   /* c++ */	
		jmp boucle2

	return0:
		movl $0, %eax
		jmp fin
		
	return1:
		movl $1, %eax
	
	fin:
		addl $8, %esp	
		leave                           /* Restore ebp and esp */
		ret                             /* Return to the caller */
