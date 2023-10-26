const int FIRST_COMPILATION  = 1 ;
const int SECOND_COMPILATION = 2 ;
const int READ_THE_NUMBER    = 1 ;
const int READ_THE_STR       = 0 ;
const int ARG_TYPE_STR       = 32;
const int ARG_TYPE_INT       = 64;
const int ARG_TYPE_TO_RAM    = 128;
const int NUM_OF_LABELS      = 10;
const int SIZE_STR           = 1000;

#define min(a, b) (((a) < (b)) ? (a) : (b))


int Read_func(struct Labels* labels,int code, int args, FILE* file, int* bin_buf, int j, char* str);
int Compilate(struct Labels* labels, struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf);
int check_len_str (FILE* file);
int Put_label(struct Labels* labels, char* str, int position, int point);
int Find_label(struct Labels* labels, int* bin_buf, char* arg);
int Push_to_bin_buf(int* bin_buf, int position, int val_comand, int arg);
