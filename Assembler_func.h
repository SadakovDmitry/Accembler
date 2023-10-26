const int FIRST_COMPILATION  = 1 ;
const int SECOND_COMPILATION = 2 ;
const int READ_THE_NUMBER    = 1 ;
const int READ_THE_STR       = 0 ;
const int ONE_ARG            = 1 ;
const int NO_ARGS            = 0 ;
const int ARG_TYPE_STR       = 32;
const int ARG_TYPE_INT       = 64;
const int ARG_TYPE_TO_RAM    = 128;
const int NUM_OF_LABELS      = 10;
const int SIZE_STR           = 1000;

#define min(a, b) (((a) < (b)) ? (a) : (b))


int Read_arg(struct Labels* labels, struct SPU* spu, int code, int num_args, FILE* file, int* bin_buf, int pos);
int Compilate(struct Labels* labels, struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf);
int check_len_str (FILE* file);
int Put_label(struct Labels* labels, char* str, int position, int point);
int Find_label(struct Labels* labels, int* bin_buf, char* arg);
int Push_to_bin_buf(int* bin_buf, int position, int val_comand, int arg);
int Processing_arg(char* arg_str, int* bin_buf, int* pos);
int Read_command_with_one_args(struct Labels* labels, struct SPU* spu, FILE* file, int* bin_buf, int pos);
int Read_command_with_no_args(int pos);
int Second_compil(struct Labels* labels,struct SPU* spu, int Num_rows, FILE* file, int* bin_buf);
void First_compil(struct Labels* labels, int Num_rows, FILE* file);
