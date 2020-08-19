#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************/
/****************************************/

/* Prints the program usage and exits */
static void usage(const char* program);

/* Creates a new empty, uninitialized matrix */
static int* matrix_create(int matorder);
/* Creates a new empty, uninitialized vector */
static int* vector_create(int matorder);
/* Parses a text file and creates a new matrix from that data */
static void matrix_parse(const char* datafn, int** matdata, int* matorder);
/* Frees the memory from the given matrix */
static void matrix_free(int* matdata);

/* Prints the data of a matrix */
extern void matrix_print(const char* msg, int* matdata, int matorder);
/* Prints the data of a vector */
extern void vector_print(const char* msg, int* matdata, int matorder);

/* Compares two matrices and returns 1 if they're identical, 0 if not */
static int matrix_equals(const int* inmatdata1, const int* inmatdata2, int matorder);
/* Compares two vectors and returns 1 if they're identical, 0 if not */
static int vector_equals(const int* inmatdata1, const int* inmatdata2, int veclen);
/* Calculate the transpose of a matrix */
static void matrix_transpose(const int* inmatdata, int* outmatdata, int matorder);
/* Calculate the diagonal matrix of a matrix */
static void matrix_diagonal(const int* inmatdata, int* outmatdata, int matorder);
/* Calculate the multiplication between two matrices */
static void matrix_column_aver(const int* inmatdata, int* outmatdata, int matorder);
/* Calculate the multiplication between two matrices */
static void matrix_multiply(const int* inmatdata1, const int* inmatdata2, int* outmatdata, int matorder);

/* Functions to implement in assembler */
extern int matrix_equals_asm(const int* inmatdata1, const int* inmatdata2, int matorder);
extern void matrix_transpose_asm(const int* inmatdata, int* outmatdata, int matorder);
extern void matrix_diagonal_asm(const int* inmatdata, int* outmatdata, int matorder);
extern void matrix_column_aver_asm(const int* inmatdata, int* outmatdata, int matorder);
extern void matrix_multiply_asm(const int* inmatdata1, const int* inmatdata2, int* outmatdata, int matorder);

/****************************************/
/****************************************/

int main(int argc, char** argv) {
   /* Variables */
   char* datafn;       /* The name of the data file */
   int* matdata;       /* The matrix data */
   int matorder;       /* The matrix order */
   int* transposec;    /* The transpose matrix calculated with the C function */
   int* transposeasm;  /* The transpose matrix calculated with the assembler function */
   int* diagonalc;     /* The diagonal matrix calculated with the C function */
   int* diagonalasm;    /* The diagonal matrix calculated with the assembler function */
   int* multipliedc;   /* The multiplied matrix calculated with the C function */
   int* multipliedasm; /* The multiplied matrix calculated with the assembler function */
   int* columnavervectorc;   /* The single row vector with column average values with the C function */
   int* columnavervectorasm; /* The single row vector with column average values with the assembler function */
   /* Program logic */
   printf("=========================\n");
   printf("=== Matrix operations ===\n");
   printf("=========================\n\n");
   /* Parse data file name */
   if(argc != 2) usage(argv[0]);
   datafn = strdup(argv[1]);
   /* Parse data from file */
   matrix_parse(datafn, &matdata, &matorder);
   matrix_print("original", matdata, matorder);
   /* Calculate reference transpose matrix */
   transposec = matrix_create(matorder);
   matrix_transpose(matdata, transposec, matorder);
   matrix_print("transpose (C function)", transposec, matorder);
   /* Calculate reference diagonal matrix */
   diagonalc = matrix_create(matorder);
   matrix_diagonal(matdata, diagonalc, matorder);
   matrix_print("diagonal (C function)", diagonalc, matorder);
   /* Calculate reference average vector */
   columnavervectorc = vector_create(matorder);
   matrix_column_aver(matdata, columnavervectorc, matorder);
   vector_print("average vector (C function)", columnavervectorc, matorder);
   /* Calculate reference multiplication of matrix and transpose */
   multipliedc = matrix_create(matorder);
   matrix_multiply(matdata, transposec, multipliedc, matorder);
   matrix_print("original x transpose (C function)", multipliedc, matorder);
   /* Test assembler equality function */
   if(matrix_equals_asm(matdata, matdata, matorder) == 1)
      printf("OK: equality test with original matrix passed (assembler function)\n\n");
   else {
      printf("FAIL: equality test with original matrix failed (assembler function)\n\n");
      exit(1);
   }
   if(matrix_equals_asm(matdata, transposec, matorder) == 0)
      printf("OK: inequality test between original and reference transpose passed (assembler function)\n\n");
   else {
      printf("FAIL: inequality test between original and reference transpose failed (assembler function)\n\n");
      exit(1);
   }
   /* Test assembler function for transpose */
   transposeasm = matrix_create(matorder);
   matrix_transpose_asm(matdata, transposeasm, matorder);
   matrix_print("transpose (assembler function)", transposeasm, matorder);
   if(matrix_equals(transposec, transposeasm, matorder) == 1)
      printf("OK: transpose calculated with assembly function matches reference\n\n");
   else {
      printf("FAIL: transpose calculated with assembly function does not match reference\n\n");
      exit(1);
   }
   /* Test assembler function for diagonal */
   diagonalasm = matrix_create(matorder);
   matrix_diagonal_asm(matdata, diagonalasm, matorder);
   matrix_print("transpose (assembler function)", diagonalasm, matorder);
   if(matrix_equals(diagonalc, diagonalasm, matorder) == 1)
      printf("OK: diagonal calculated with assembly function matches reference\n\n");
   else {
      printf("FAIL: diagoanl calculated with assembly function does not match reference\n\n");
      exit(1);
   }
   /* Test assembler function for multiplication */
   multipliedasm = matrix_create(matorder);
   matrix_multiply_asm(matdata, transposeasm, multipliedasm, matorder);
   matrix_print("original x transpose (assembler function)", multipliedasm, matorder);
   if(matrix_equals(transposec, transposeasm, matorder) == 1)
      printf("OK: multiplication calculated with assembly function matches reference\n\n");
   else {
      printf("FAIL: multiplication calculated with assembly function does not match reference\n\n");
      exit(1);
   }
   /* Test assembler function for column average */
   columnavervectorasm = vector_create(matorder);
   matrix_column_aver_asm(matdata, columnavervectorasm, matorder);
   vector_print("average vector (assembler function)", columnavervectorasm, matorder);
   if(vector_equals(columnavervectorc, columnavervectorasm, matorder) == 1)
      printf("OK: average vector with assembly function matches reference\n\n");
   else {
      printf("FAIL: average vector calculated with assembly function does not match reference\n\n");
      exit(1);
   }
   /* Cleanup */
   free(datafn);
   matrix_free(matdata);
   matrix_free(transposec);
   matrix_free(transposeasm);
   matrix_free(multipliedc);
   matrix_free(multipliedasm);
   matrix_free(diagonalc);
   matrix_free(diagonalasm);
   matrix_free(columnavervectorc);
   matrix_free(columnavervectorasm);
   return 0;
}

/****************************************/
/****************************************/

void usage(const char* program) {
   fprintf(stderr, "Usage:\n\t%s <filename>\n", program);
   exit(1);
}

/****************************************/
/****************************************/

int* matrix_create(int matorder) {
   return (int*)malloc(sizeof(int) * matorder * matorder);
}

/****************************************/
/****************************************/
int* vector_create(int matorder) {
   return (int*)malloc(sizeof(int) * matorder);
}

/****************************************/
/****************************************/

static int count_elems(char* line) {
   /* Variables */
   char* curptr; /* Pointer to current char in line */
   int count;    /* Element counter */
   /* Count number of spaces */
   curptr = line;
   count = 0;
   while(*curptr != 0) {
      if(*curptr == ' ') ++count;
      ++curptr;
   }
   /* Number of elements = number of spaces + 1 */
   return count + 1;
}

static char* read_line(FILE* fd, size_t* len) {
  /* Variables */
  static char* buf = NULL; /* Line buffer */
  static size_t bufsz = 0; /* Size of line buffer */
  char* newbuf;            /* New buffer allocation */
  /* Create buffer if necessary */
  if(buf == NULL) {
    bufsz = 1024;
    buf = (char*)malloc(bufsz);
  }
  /* Make sure last character in buffer is not string termination */
  buf[bufsz - 1] = 1;
  /* Start reading line */
  if(fgets(buf, bufsz, fd) == NULL) return NULL;
  /* Is the line complete? */
  while(buf[bufsz-1] == 0 && buf[bufsz-2] != '\n') {
    /* The line is not complete, we need to keep reading */
    /* Enlarge existing buffer */
    newbuf = (char*)realloc(buf, bufsz * 2);
    if(newbuf == NULL) return NULL;
    buf = newbuf;
    bufsz *= 2;
    /* Make sure last character in buffer is not string termination */
    buf[bufsz - 1] = 1;
    /* Read more from the line */
    if(fgets(buf + bufsz/2-1, bufsz/2+1, fd) == NULL) return NULL;
  }
  /* Update line length */
  *len = strlen(buf);
  /* Return line data */
  return buf;
}

void matrix_parse(const char* datafn, int** matdata, int* matorder) {
   /* Variables */
   FILE* fd;       /* File stream */
   char* line;     /* Line of data */
   size_t linelen; /* Size of the line of data */
   char* elem;     /* Element in the line */
   int r;          /* Current row index */
   int c;          /* Current column index */
   /* Open data file for reading */
   fd = fopen(datafn, "r");
   if(fd == NULL) {
      perror(datafn);
      exit(1);
   }
   /* Count number of elements in first row */
   line = read_line(fd, &linelen);
   line[linelen-1] = 0;
   *matorder = count_elems(line);
   /* Create data buffer for matrix */
   *matdata = matrix_create(*matorder);
   /* Parse data, one line at a time */
   r = 0;
   do {
      /* First element in the line of data */
      c = 0;
      /* Go through each element in the line, ignore extra */
      while((c < *matorder) && ((elem = strsep(&line, " ")) != NULL)) {
         (*matdata)[c + r * (*matorder)] = strtol(elem, NULL, 10);
         ++c;
      }
      /* Make sure you read the right number of elements */
      if(c != *matorder) {
         fprintf(stderr, "%s: expected %d elements at row %d, found %d instead\n",
                 datafn, *matorder, r, c);
         exit(1);
      }
      /* Row filled, get to the next one */
      ++r;
      line = read_line(fd, &linelen);
      if(line != NULL)
         line[linelen-1] = 0;
   }
   while(r < *matorder && line != NULL);
   /* Make sure you read the right number of elements */
   if(r != *matorder) {
      fprintf(stderr, "%s: expected %d rows, found %d instead\n",
              datafn, *matorder, r);
      exit(1);
   }
   /* Close file */
   fclose(fd);
}

/****************************************/
/****************************************/

void matrix_free(int* matdata) {
   free(matdata);
}

/****************************************/
/****************************************/

void matrix_print(const char* msg, int* matdata, int matorder) {
   /* Variables */
   int r, c; /* Row/column indices */
   printf("%s = \n", msg);
   /* Go through elements */
   for(r = 0; r < matorder; ++r) {
      printf("\t| %5d", matdata[r * matorder]);
      for(c = 1; c < matorder; ++c) {
         printf(" %5d", matdata[c + r * matorder]);
      }
      printf(" |\n\n");
   }
   printf("\n");
}

/****************************************/
/****************************************/

void vector_print(const char* msg, int* matdata, int matorder) {
   /* Variables */
   int c; /* Row/column indices */
   printf("%s = \n", msg);
   /* Go through elements */
   for(c = 0; c < matorder; ++c) {
	  if(c==0){printf("\t| %5d", matdata[c]);}
      else{printf(" %5d", matdata[c]);}
   }
   printf(" |\n\n");
}

/****************************************/
/****************************************/

int matrix_equals(const int* inmatdata1, const int* inmatdata2, int matorder) {
   /* Variables */
   int r, c; /* Row/column indices */
   /* Go through elements */
   for(r = 0; r < matorder; ++r) {
      for(c = 0; c < matorder; ++c) {
         if(inmatdata1[c + r * matorder] != inmatdata2[c + r * matorder])
            return 0;
      }
   }
   return 1;
}

/****************************************/
/****************************************/

int vector_equals(const int* inmatdata1, const int* inmatdata2, int veclen) {
   /* Variables */
   int c; /* Row/column indices */
   /* Go through elements */
   for(c = 0; c < veclen; ++c) {
      if(inmatdata1[c ] != inmatdata2[c])
            return 0;
      
   }
   return 1;
}

/****************************************/
/****************************************/

void matrix_transpose(const int* inmatdata, int* outmatdata, int matorder) {
   /* Variables */
   int r, c; /* Row/column indices */
   /* Go through the matrix elements */
   for(r = 0; r < matorder; ++r) {
      for(c = 0; c < matorder; ++c) {
         outmatdata[c + r * matorder] = inmatdata[r + c * matorder];
      }
   }
}

/****************************************/
/****************************************/

void matrix_diagonal(const int* inmatdata, int* outmatdata, int matorder) {
   /* Variables */
   int r, c; /* Row/column indices */
   /* Go through the matrix elements */
   for(r = 0; r < matorder; ++r) {
      for(c = 0; c < matorder; ++c) {
		if(c == r){
			outmatdata[c + r * matorder] = inmatdata[c + r * matorder];
		} 
        else{
			outmatdata[c + r * matorder] = 0;
		}
      }
   }
}

/****************************************/
/****************************************/

void matrix_multiply(const int* inmatdata1, const int* inmatdata2, int* outmatdata, int matorder) {
   /* Variables */
   int r, c; /* Row/column indices */
   int i;    /* Index for element calculation */
   int elem; /* Buffer for element calculation */
   /* Perform row x column multiplication */
   for(r = 0; r < matorder; ++r) {
      for(c = 0; c < matorder; ++c) {
         elem = 0;
         for(i = 0; i < matorder; ++i)
            elem += inmatdata1[i + r * matorder] * inmatdata2[c + i * matorder];
         outmatdata[c + r * matorder] = elem;
      }
   }
}

/****************************************/
/****************************************/

void matrix_column_aver(const int* inmatdata, int* outmatdata, int matorder) {
   /* Variables */
   int r, c; /* Row/column indices */
   int elem; /* Buffer for element calculation */
   /* Perform row x column multiplication */
   for(c = 0; c < matorder; ++c) {
	  elem = 0;
      for(r = 0; r < matorder; ++r) {
         elem += inmatdata[c + r * matorder];         
      }
	  outmatdata[c] = elem/matorder;
   }
}

/****************************************/
/****************************************/
