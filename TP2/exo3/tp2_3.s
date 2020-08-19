.data
.global func_s

func_s:	
	
		mov $0, %esi
		mov $10, %edi
	again: 
		cmp %edi, %esi
		ja done
		mov a, %eax
		mov b, %ebx
		mov e, %edx
		add %edx, %eax
		sub %ebx, %eax
		mov %eax, a

	if:
		mov e, %edx
		add $1, %edx
		cmp %edx, %esi
		jna next
		mov b, %ebx
		mov c, %ecx
		add $2, %ecx
		cmp %ecx, %ebx 
		jne else
	next:
		mov a, %eax	
		mov c, %ecx
		mov e, %edx
		add %ecx, %eax
		sub %edx, %eax
		mov %eax, a	

		mov b, %ebx
		add $2, %ebx
		mov %ebx, b	
		
		add $1, %esi
		jmp again
	else:
		mov a, %eax	
		mov c, %ecx
		add d, %eax
		sub %ecx, %eax
		mov %eax, a	
		
		mov c, %ecx
		sub $1, %ecx
		mov %ecx, c	
		
		add $1, %esi	
		jmp again		

	done:
	
		ret
