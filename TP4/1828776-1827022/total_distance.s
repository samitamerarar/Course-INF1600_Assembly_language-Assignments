.globl _ZNK4CCar12TotalDistAsmEv

_ZNK4CCar12TotalDistAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
	
	movl 8(%ebp), %eax      # adresse objet

	fld 4(%eax)             # s0 --> st0
	fld 32(%eax)            # st_asm --> st0, s0 --> st1
	fsubp                   # st_asm - s0 --> st0; return st0
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
