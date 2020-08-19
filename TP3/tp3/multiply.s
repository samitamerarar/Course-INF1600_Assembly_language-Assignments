.globl matrix_multiply_asm

matrix_multiply_asm:
		push %ebp                      /* Save old base pointer */
		mov %esp, %ebp                 /* Set ebp to current esp */
		sub $16, %esp
		movl $0, -4(%ebp)              /* r = 0 */
		movl $0, -8(%ebp)              /* c = 0 */
		movl $0, -12(%ebp)             /* i = 0 */
		movl $0, -16(%ebp)             /* elem = 0 */
		
	boucle1:
		movl -4(%ebp), %eax            
		cmp 20(%ebp), %eax             /* Compare matorder et r */
		jae fin
		
	boucle2:
		movl -8(%ebp), %eax
		cmp 20(%ebp), %eax             /* Compare matorder et c */
		jl boucle3
		
		incl -4(%ebp)                  /* r++ */
		movl $0, -8(%ebp)              /* c = 0 */ 
		jmp boucle1
		
	boucle3:
		movl -12(%ebp), %eax
		cmp 20(%ebp), %eax             /* Compare matorder et i */
		jl situation1
		
		movl $0, -16(%ebp)             /* elem = 0 */
		incl -8(%ebp)                  /* c++ */
		movl $0, -12(%ebp)             /* i = 0 */
		jmp boucle2
		
		
	situation1:
		
		movl 20(%ebp), %eax            /* indice de inmatdata1 */
		imull -4(%ebp), %eax
		addl -12(%ebp), %eax           /* i+r*matorder */
		
		movl 20(%ebp), %ebx            /* indice de inmatdata2 */
		imull -12(%ebp), %ebx
		addl -8(%ebp), %ebx            /* c+i*matorder */
		
		movl 8(%ebp), %ecx             /* inmatdata1 */
		movl (%ecx, %eax, 4), %ecx     /* inmatdata1[i+r*matorder] */

		movl 12(%ebp), %edx            /* inmatdata2 */
		movl (%edx, %ebx, 4), %edx     /* inmatdata2[c+i*matorder] */
		
		imull %ecx, %edx               /* inmatdata1[i+r*matorder] * inmatdata2[c+i*matorder] */
		
		xor %eax, %eax
		
		addl %edx, -16(%ebp)           /* elem += inmatdata1Element * inmatdata2Element */
		movl -16(%ebp), %eax           /* elem */
		
		movl 20(%ebp), %edi            /* indice outmatdata */
		imull -4(%ebp), %edi
		addl -8(%ebp), %edi            /* c+r*matorder */
		
		movl 16(%ebp), %esi            /* outmatdata */
		movl %eax, (%esi, %edi, 4)     /* outmatdata[c+r*matorder] = elem */
		
		incl -12(%ebp)                 /* i++ */
		jmp boucle3

	fin:
		addl $16, %esp
		leave                          /* Restore ebp and esp */
		ret                            /* Return to the caller */
