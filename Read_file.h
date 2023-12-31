#include "enum_commands.h"

typedef int Elem_t;

struct About_text{
    int rows;
    int text_size;
    char* id_buf;
    int first_or_second_file;
};

struct About_str{
    char* str;
    int len;
};

struct Labels {
        char* point_name;
        int ip;
};

struct SPU{
    Elem_t* RAM;
    int* bin_buf;
    Elem_t* args;
    unsigned int SPU_err;
    Labels* label;
};


enum SPU_ERR : unsigned int
{
    ARGS_NULL               = 1 << 0,
    INCORRECT_INPUT         = 1 << 1,
    INCORRECT_COMAND        = 1 << 2,
    SQRT_FROM_INCORRECT_NUM = 1 << 3
};


const int LEN_STR_RAM = 400;


int Size_of_text(int* Num_rows, FILE* file);
struct About_str* Input_text (int Num_rows, char* buffer, FILE* file);
void Make_bin_file(struct About_text* ab_text, struct About_str* ab_str);
struct About_str* Work_with_input_file(struct About_text* ab_text, char* buffer, int* Num_rows, FILE* file);
void Clean_buf();
void fill_struct( struct About_text* ab_text, int* Num_rows, int size_of_text, char* buffer);
enum Comands Convert_to_numbers(struct About_str* ab_str, char * now_comand, int i);
int Convert_to_comands(struct SPU* spu, FILE* output_file);
void Convert_to_cheak_file(struct About_text* ab_text, struct SPU* spu);
int* Work_with_bin_file(struct About_text* ab_text, FILE* file);
void Print_RAM(struct SPU* spu, int size_of_RAM );
void Print_bin_buf(int* bin_buf, int size_bin_buf);
void Print_VRAM(struct SPU* spu, int size_of_RAM);
