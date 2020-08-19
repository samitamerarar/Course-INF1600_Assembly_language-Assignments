.globl matrix_transpose_asm

matrix_transpose_asm:
		push %ebp                       /* Save old base pointer */
		mov %esp, %ebp                  /* Set ebp to current esp */
		subl $8, %esp
		movl $0, -4(%ebp)               /* r = 0 */
		movl $0, -8(%ebp)               /* c = 0 */

	boucle1:
		movl -4(%ebp), %eax 
		cmp 16(%ebp), %eax              /* Compare matorder et r */
		jae fin

	boucle2:
		movl -8(%ebp), %eax 
		cmp 16(%ebp), %eax              /* Compare matorder et c */
		jl situation1

		incl -4(%ebp)                   /* r++ */
		movl $0, -8(%ebp)               /* c = 0 */
		jmp boucle1			
		
	situation1:
		movl 16(%ebp), %eax             /* indice de outmatdata */
		imull -4(%ebp), %eax
		addl -8(%ebp), %eax             /* c+r*matorder */

		movl 16(%ebp), %ebx             /* indice de inmatdata */
		imull -8(%ebp), %ebx		
		addl -4(%ebp), %ebx             /* r+c*matorder */
		
		movl 8(%ebp), %edx              /* pointeur au debut du tableau inmatdata */
		movl (%edx, %ebx, 4), %edx      /* l'élément à [r+c*matorder] de inmatdata */
		movl 12(%ebp), %ecx             /* pointeur au debut du tableau outmatdata */
		movl %edx, (%ecx, %eax, 4)      /* outmatdata[c+r*matorder] = inmatdata[r+c*matorder] */

		incl -8(%ebp)                   /* c++ */
		jmp boucle2

	fin:
		addl $8, %esp
		leave                           /* Restore ebp and esp */
		ret                             /* Return to the caller */
