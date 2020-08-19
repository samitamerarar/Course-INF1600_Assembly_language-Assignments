.globl _ZNK4CCar15AverageSpeedAsmEv

_ZNK4CCar15AverageSpeedAsmEv:
		push %ebp      /* save old base pointer */
		mov %esp, %ebp /* set ebp to current esp */
	
		movl 8(%ebp), %eax      # adresse objet

	condition:
		fldz                    # 0 --> st0
		fld 52(%eax)            # started --> st0, 0 --> st1
		fcomi                   # comparer 2 floats
		je returnv0             

	return_autre:
		movl (%eax), %ebx
		push %eax               
		call *32(%ebx)          # TotalDistAsm(), totS --> st0
		fld 52(%eax)            # started --> st0, totS --> st1
		fdivrp                  # totS/started
		pop %eax
		jmp fin                 # return (totS/started)
		
	returnv0:
		fld 8(%eax)             # return v0 

        fin:
		leave          /* restore ebp and esp */
		ret            /* return to the caller */
