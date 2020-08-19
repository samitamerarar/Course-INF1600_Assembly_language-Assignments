.data
        factor: .float 0.5 /* use this to multiply by 0.5 */

.text

.globl _ZN4CCar15UpdateStatusAsmEv

_ZN4CCar15UpdateStatusAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
	
	movl 8(%ebp), %eax      # adresse objet

	fld 48(%eax)            # interv --> st0
	fld 48(%eax)            # interv --> st0 et st1
	fmulp                   # (interv*interv) --> st0
	fld 40(%eax)            # at_asm --> st0, (interv*interv) --> st1
	fmulp                   # (at_asm*interv*interv) --> st0
	fld factor              # 0.5 --> st0, (at_asm*interv*interv) --> st1
	fmulp                   # (0.5*at_asm*interv*interv) --> st0

	fld 36(%eax)            # vt_asm --> st0, (0.5*at_asm*interv*interv) --> st1
	fld 48(%eax)            # interv --> st0, vtc_asm --> st1
	fmulp                   # (vtc_asm*interv) --> st0
	faddp                   # (vt_asm*interv)+(0.5*at_asm*interv*interv) --> st0
	fld 32(%eax)            # st_asm --> st0 
	faddp                   # st_asm + (vt_asm*interv) + (0.5*at_asm*interv*interv)
	fstp 32(%eax)           # st_asm = st_asm+(vt_asm*interv) + (0.5*at_asm*interv*interv)

	fld 48(%eax)            # interv --> st0
	fld 40(%eax)            # at_asm --> st0, interv --> st1
	fmulp                   # at_asm*interv
	fld 36(%eax)            # vt_asm --> st0
	faddp                   # vt_asm + at_asm*interv
	fstp 36(%eax)           # vt_asm = vtc_asm + at_asm*interv
	
	fld 52(%eax)            # started --> st0
	fld 48(%eax)            # interv --> st0, started --> st1
	faddp                   # started + interv
	fstp 52(%eax)           # started += interv
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
