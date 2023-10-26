#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
#include <sys/stat.h>
#include "Read_file.h"
//#include "enum_commands.h"


#define MAKE_COLOUR(colour) printf("\033[%sm%c \033[0m", colour, (char) *(spu -> RAM + j + i * len_of_row));
//#define MAKE_COLOUR(colour) colour

const int MAX_NUM = 10000;



void fill_struct( struct About_text* ab_text, int* Num_rows, int size_of_text, char* buffer)
{
    assert(ab_text != NULL);

    ab_text -> rows = *Num_rows;
    ab_text -> text_size = size_of_text;
    ab_text -> id_buf = buffer;
}

int Size_of_text(int* Num_rows, FILE* file )
{
    //FILE* file = fopen(FILE_NAME, "r");

    assert ( file != NULL );
    int size_of_file = 0;
    char input = 0;

    while ((input = fgetc(file)) != EOF)
    {
        if (input == ' ')
        {
            size_of_file++;
        }

        if (input == '\n')
        {
            (*Num_rows)++;
        }
    }
    return size_of_file;
}


struct About_str* Input_text (int Num_rows, char* buffer, FILE* file) {

    assert(buffer != NULL);
    assert ( file != NULL );


    int i = 0;
    int now_index_buf = 0;

    struct About_str* ab_str = ( struct About_str* ) calloc ( Num_rows + 1 , sizeof ( struct About_str ));

    while ( true )
    {
        char *input = fgets ( ( char* ) (buffer + now_index_buf), MAX_NUM, file );
        if ( input == NULL )
        {
            break;
        }

        int len = strlen ( input );
        char* index = ( char* ) calloc ( ( len + 1 ), sizeof ( char ) );
        char* spot_for_cpy =  strncpy ( index,  (buffer + now_index_buf), len + 1 );
        ab_str[i].str = spot_for_cpy;
        ab_str[i].len = len;
        now_index_buf = now_index_buf + ab_str[i].len;
        i++;
    }

    return ab_str;
}


struct About_str* Work_with_input_file(struct About_text* ab_text, char* buffer, int* Num_rows, FILE* file)
{

    Size_of_text (Num_rows, file);                                                                                                                //nado ispravit
    int size_of_text = (*Num_rows) * 3;

    buffer = (char*) calloc (size_of_text * 100, sizeof(char));                                                                                   //nado ispravit

    if (ab_text -> first_or_second_file == 1)
    {
        file = fopen("Text_comands.txt", "r");
    }
    else
    {
        file = fopen("Numbered_comands.txt", "r");
    }

    struct About_str* ab_str = Input_text (*(Num_rows), buffer, file);

    fill_struct( ab_text, Num_rows, size_of_text, buffer);
    assert(ab_str != NULL);
    //Clean_buf();

    return ab_str;
}


int* Work_with_bin_file(struct About_text* ab_text, FILE* file)
{
    struct stat st = {};
    stat("code_bin.bin", &st);

    int* bin_buf = (int*) calloc (st.st_size + 1, sizeof(char));
    fread(bin_buf, sizeof (int), st.st_size, file);

    ab_text -> text_size = st.st_size;
    //Clean_buf();

    return bin_buf;
}

/*
void Choose_colour(int colour, struct SPU* spu, int i, int j, int len_of_row)
{
    switch(colour)
    {
    case 29:
        printf("\033[29m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    case 30:
        printf("\033[30m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    case 31:
        printf("\033[31m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    case 32:
        printf("\033[32m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    case 33:
        printf("\033[33m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    case 34:
        printf("\033[34m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    case 35:
        printf("\033[35m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    case 36:
        printf("\033[36m%c \033[0m", (char) *(spu -> RAM + j + i * len_of_row));
        break;
    }
}
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define DEF_CMD(name, code, num_args, program)                                                                                                      \
    if (func_num == (code | 128 | 64))                                                                                                              \
    {                                                                                                                                               \
        fprintf(output_file, "%ld\t\t"#name, spu -> bin_buf - start_buf);                                                                           \
        fprintf(output_file, " [%d]\n", *(spu -> bin_buf + 1));                                                                                     \
        spu -> bin_buf = spu -> bin_buf + 2;                                                                                                        \
        continue;                                                                                                                                   \
    }                                                                                                                                               \
    if (func_num == (code | 128 | 32))                                                                                                              \
    {                                                                                                                                               \
        fprintf(output_file, "%ld\t\t"#name, spu -> bin_buf - start_buf);                                                                           \
        fprintf(output_file, " [r%cx]\n", (char)((int)simbol_a + *(spu -> bin_buf + 1)));                                                           \
        spu -> bin_buf = spu -> bin_buf + 2;                                                                                                        \
        continue;                                                                                                                                   \
    }                                                                                                                                               \
    if (func_num == (code | 64))                                                                                                                    \
    {                                                                                                                                               \
        fprintf(output_file, "%ld\t\t"#name, spu -> bin_buf - start_buf);                                                                           \
        fprintf(output_file, " %d\n", *(spu -> bin_buf + 1));                                                                                       \
        spu -> bin_buf = spu -> bin_buf + 2;                                                                                                        \
        continue;                                                                                                                                   \
    }                                                                                                                                               \
    if (func_num == (code | 32))                                                                                                                    \
    {                                                                                                                                               \
        fprintf(output_file, "%ld\t\t"#name, spu -> bin_buf - start_buf);                                                                           \
        fprintf(output_file, " r%cx\n", (char)((int)simbol_a + *(spu -> bin_buf + 1)));                                                             \
        spu -> bin_buf = spu -> bin_buf + 2;                                                                                                        \
        continue;                                                                                                                                   \
    }                                                                                                                                               \
    if (func_num == code)                                                                                                                           \
    {                                                                                                                                               \
        fprintf(output_file, "%ld\t\t"#name"\n", spu -> bin_buf - start_buf);                                                                       \
        spu -> bin_buf = spu -> bin_buf + 1;                                                                                                        \
    }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Convert_to_cheak_file(struct About_text* ab_text, struct SPU* spu)
{
    assert(ab_text != NULL);
    assert(spu -> bin_buf != NULL);

    FILE* output_file = fopen("Cheak_file.txt", "w");

    assert(output_file != NULL);

    int func_num = 0;
    int arg_type = 0;
    int input_func = 0;
    int simbol_a = 'a';
    char str[1000] = "";
    int* start_buf = spu -> bin_buf;

    while(func_num != CMD_HLT)
    {
        func_num = *(spu -> bin_buf);
        #include "commands.h"
    }

    fclose(output_file);
    #undef DEF_CMD
}


void Print_RAM(struct SPU* spu, int size_of_RAM)
{
    FILE* RAM_txt = fopen("RAM.txt", "w");

    int len_of_row = 200;
    int num_of_rows = (int) size_of_RAM / len_of_row;

    for (int i = 0; i < num_of_rows; i++)
    {
        for (int j = 0; j < len_of_row; j++)
        {
            fprintf(RAM_txt, "%4d ",*(spu -> RAM + j + i * len_of_row));
            //printf("%4d ",*(spu -> RAM + j + i * len_of_row));
        }
        fprintf(RAM_txt, "\n");
        //printf("\n");
    }
    fclose(RAM_txt);
}



void Print_VRAM(struct SPU* spu, int size_of_RAM)
{
    int len_of_row = 200;
    int num_of_rows = (int) size_of_RAM / len_of_row;
    char colour[10] = "";

    for (int i = 0; i < num_of_rows; i++)
    {
        for (int j = 1; j < len_of_row; j = j + 2)
        {

            //snprintf(colour, strlen(colour), "%d", *(spu -> RAM + j + i * len_of_row + 1));
            //set_colour(*(spu -> RAM + j + i * len_of_row + 1))
            //textcolour(*(spu -> RAM + j + i * len_of_row));
            int code = *(spu -> RAM + j + i * len_of_row - 1);
            snprintf(colour, sizeof colour, "%d", code);
            //printf("colour = %s\n", colour);

            MAKE_COLOUR(colour)
            //Choose_colour(code, spu, i, j, len_of_row);
        }
        printf("\n");
    }
}


void Print_bin_buf(int* bin_buf, int size_bin_buf)
{
    for (int i = 0; i < size_bin_buf; i++)
    {
        printf ("%d ", *(bin_buf + i));
    }
}
