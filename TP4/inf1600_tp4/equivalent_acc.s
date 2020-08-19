.data
        factor: .float 2.0 /* utilise pour multiplier par 2.0 */

.text

.globl _ZNK4CCar16EquivalentAccAsmEv

_ZNK4CCar16EquivalentAccAsmEv:
	push %ebp      /* save old base pointer */
	mov %esp, %ebp /* set ebp to current esp */

	movl 8(%ebp), %eax      # adresse objet

	movl (%eax), %ebx
	push %eax
	call *32(%ebx)          # totS = totaldistAsm() --> st0
	pop %eax
	
	fld factor              # 2.0 --> st0, totS --> st1
	fmulp                   # 2.0*totS --> st0
	fld 52(%eax)
	fld 52(%eax)            # started --> st0, started --> st1
	fmulp                   # started * started
	fdivrp                  # (2.0*totS)/(started*started) --> st0
	                        # return st0

	leave          /* restore ebp and esp */
	ret            /* return to the caller */
