.global func_s

func_s:
	flds c		
	flds d		
	flds e		
	faddp		
	faddp		
	flds g		
	fmulp 		
	fstps a		
	flds b		
	flds f		
	fsubp		
	flds d		
	flds e		
	fmulp		
	fdivrp		
	flds a		
	fmulp		
	fstps a		
	flds g			
	flds d		
	fdivrp		
	flds b		
	faddp		
	flds a		
	fsubp		
	fstps a		
	
	ret
