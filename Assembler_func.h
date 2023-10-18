const int FIRST_COMPILATION  = 1 ;
const int SECOND_COMPILATION = 2 ;
const int READ_THE_NUMBER    = 1 ;
const int READ_THE_STR       = 0 ;
const int ARG_TYPE_STR       = 32;
const int ARG_TYPE_INT       = 64;
const int NUM_OF_LABELS      = 10;

#define max(a, b) (((a) < (b)) ? (a) : (b))




int Read_func(struct Labels* labels,int code, int args, FILE* file, int* bin_buf, int j, char* str);
int Compilate(struct Labels* labels, struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf);
