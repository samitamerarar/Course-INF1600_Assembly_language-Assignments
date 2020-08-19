#include <stdio.h>

unsigned int Decryption_fct(unsigned int crypted,unsigned int key) //1,2 (je pense)
{
	unsigned int decrypted; //0 (je pense)

	/*
	 * Remplacez le code suivant par de l'assembleur en ligne
	 * en utilisant le moins d'instructions possible
	
	permutation de décryptage; 4 bit = 1 nibble
	crypted[nib1,nib2,nib3,nib4,nib5,nib6,nib7,nib8] -->
	--> decrypted[nib5,nib4,nib8,nib1,nib6,nib2,nib3,nib7]
	

	decrypted = ((crypted & 0xf0000000) >> 12 |
		     (crypted & 0xf000000)  >> 16 |
		     (crypted & 0xf00000)   >> 16 |
		     (crypted & 0xf0000)    << 8  |
		     (crypted & 0xf000)     << 16 |
		     (crypted & 0xf00)      << 4  |
		     (crypted & 0xf0)       >> 4  |
		     (crypted & 0xf)        << 20 )  |
		     key;
	
	
	*/
	asm volatile (
		"ror $4, %1\n\t"       // [8,1,2,3,4,5,6,7]

		"movl %1, %0\n\t"      // [8,1,2,3,4,5,6,7]
		"shl $8, %0\n\t"       // [2,3,4,5,6,7,0,0]
		"shr $12, %0\n\t"      // [0,0,0,2,3,4,5,6]

		"movl %0, %%ebx\n\t"   // [0,0,0,2,3,4,5,6]
		"shl $28, %%ebx\n\t"   // [6,0,0,0,0,0,0,0]
		"shr $8, %%ebx\n\t"    // [0,0,6,0,0,0,0,0]
		"xor %0, %%ebx\n\t"    // [0,0,6,2,3,4,5,6]
		"shr $4, %%ebx\n\t"    // [0,0,0,6,2,3,4,5]
		"shl $4, %%ebx\n\t"    // [0,0,6,2,3,4,5,0]

		"movl %1, %0\n\t"      // [8,1,2,3,4,5,6,7]
		"shr $24, %0\n\t"      // [0,0,0,0,0,0,8,1]
		"shl $24, %0\n\t"      // [8,1,0,0,0,0,0,0]
		
		"xor %0, %%ebx\n\t"    // [8,1,6,2,3,4,5,0]
		
		"movl %1, %0\n\t"      // [8,1,2,3,4,5,6,7]	
		"shl $28, %0\n\t"      // [7,0,0,0,0,0,0,0]
		"shr $28, %0\n\t"      // [0,0,0,0,0,0,0,7]
			
		"shr $4, %%ebx\n\t"    // [0,8,1,6,2,3,4,5]
		"ror $4, %%ebx\n\t"    // [5,0,8,1,6,2,3,4]
		"shr $4, %%ebx\n\t"    // [0,5,0,8,1,6,2,3]
		"shl $4, %%ebx\n\t"    // [5,0,8,1,6,2,3,0]
		"xor %0, %%ebx\n\t"    // [5,0,8,1,6,2,3,7]

		"movl %1, %0\n\t"      // [8,1,2,3,4,5,6,7]	
		"shr $12, %0\n\t"      // [0,0,0,8,1,2,3,4]
		"shl $28, %0\n\t"      // [4,0,0,0,0,0,0,0]
		"shr $4, %0\n\t"       // [0,4,0,0,0,0,0,0]

		"xor %%ebx, %0\n\t"    // [5,4,8,1,6,2,3,7]

		"or %2, %0\n\t"
		
		:"=a"(decrypted)// sorties (s'il y a lieu)
		:"c"(crypted), "d"(key)// entrées
		:"%ebx" // registres modifiés (s'il y a lieu)
	);
	
	return decrypted;
}

int main()
{
	unsigned int data = 0x12345678;
	unsigned int key =0x0c0180c;

	printf("Représentation cryptée  :   %08x\n"
	       "Représentation decryptée:   %08x\n",
	       data,
	       Decryption_fct(data,key));

	return 0;
}
