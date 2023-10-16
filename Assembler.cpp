
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

#include "Read_file.h"
#include "SPU_func.h"

#undef DEF_CMD

const int mask_push_reg = 0x60000000;

/*
void Read_func_input(int num_args, int arg_type, int* bin_buf, int j, FILE* file);

void Read_func_input(int code, int arg_type, int* bin_buf, int j, FILE* file)
{

    switch(
    *(bin_buf + j) |= 1 << code;
    *(bin_buf + j) |= 1 << code


}

void Read_func_input(int num_args, int arg_type, int* bin_buf, int j, FILE* file)
{
        char simbol_a = 'a';
        char arg[4] = "";
        switch (args)
        {
        case 2:
            fscanf(file, "%s", arg);
            *(bin_buf + j) = num_of_comand;

            if (strncmp(arg, "rax", 3) == 0 || strncmp(arg, "rbx", 3) == 0 || strncmp(arg, "rcx", 3) == 0 || strncmp(arg, "rdx", 3) == 0)
            {
                *(bin_buf + j + 1) = 2;
                *(bin_buf + j + 2) = (int) (arg[1]) - (int) simbol_a;
            }
            else
            {
                if (atoi(arg) == 0)
                {
                    spu.SPU_err |= INCORRECT_INPUT;
                }
                *(bin_buf + j + 1) = 1;
                *(bin_buf + j + 2) = atoi(arg);
            }

            j = j + 3;

            break;
        case 1:
            fscanf(file, "%s", arg);
            if (arg_type == 1)
            {
                if (!(strncmp(arg, "rax", 3) == 0 || strncmp(arg, "rbx", 3) == 0 || strncmp(arg, "rcx", 3) == 0 || strncmp(arg, "rdx" 3) == 0))\
                {
                    spu.SPU_err |= INCORRECT_INPUT;
                }
                *(bin_buf + j) = num_of_comand;
                *(bin_buf + j + 1) = (int) (arg[1]) - (int) simbol_a;
            }
            else{
                *(bin_buf + j) = num_of_comand;
                *(bin_buf + j + 1) = atoi(arg);
            }
            j = j + 2;

            break;
        default:
            *(bin_buf + j) = num_of_comand;
            j++;
        }
}
*/

#define DEF_CMD(name, code, args, ...)                              \
    if (str[0] == ':')                                              \
    {                                                               \
        spu.labels[str[1] - 'O'] = j;                               \
        fprintf(stderr,"j = %d\n", spu.labels[str[1] - 'O']);                              \
    }                                                               \
    else if (strcasecmp(str, #name) == 0)                           \
    {                                                               \
        int arg = 0;                                                \
        char arg_str[4] = "";                                       \
        char simbol_a = 'a';                                        \
                                                                    \
        switch(args)                                                \
        {                                                           \
        case 1:                                                     \
            switch (fscanf(file, "%d", &arg))                       \
            {                                                       \
            case 1:                                                 \
                *(bin_buf + j) |= 1 << (code + 5);                  \
                *(bin_buf + j) |= 1 << (code + 6);                  \
                *(bin_buf + j + 1) = arg;                           \
                break;                                              \
            case 0:                                                 \
                fscanf(file, "%s", arg_str);                        \
                *(bin_buf + j) |= 1 << (code + 5);                  \
                if (arg_str[0] == ':')                              \
                {                                                   \
                    *(bin_buf + j + 1) = spu.labels[arg_str[1] - 'O'];  \
                }                                                   \
                else                                                \
                {                                                   \
                    *(bin_buf + j + 1) = (int) (arg_str[1]) - (int) simbol_a;\
                }                                                   \
            }                                                       \
            j = j + 2;                                              \
            break;                                                  \
        case 0:                                                     \
            *(bin_buf + j) = code;                                  \
            j++;                                                    \
            break;                                                  \
        }                                                           \
    }                                                               \
    else



int main()
{
    struct SPU spu = {};
    int Num_rows = 0;
    spu.SPU_err = 0;

    FILE* file_to_count_rows = fopen("Text_comands.txt", "r");
    Size_of_text(&Num_rows, file_to_count_rows );
    fclose(file_to_count_rows);

    FILE* file = fopen("Text_comands.txt", "r");

    assert(file != NULL);
    spu.labels = (int*) calloc (10, sizeof(int));
    int* bin_buf = (int*) calloc (Num_rows * 10, sizeof(int));
    int j = 0;
    char str[5] = "";
    printf("%d\n", Num_rows);

    for (int i = 0; i < Num_rows + 1; i++)
    {
        fscanf(file, "%s", str);
        #include "commands.h"
        /*else*/
        {
            spu.SPU_err |= INCORRECT_COMAND;
            break;
        }

    }
    for (int i = 0; i < j; i++)
    {
        printf("%d ", *(bin_buf + i));
    }

    SPU_DUMP(&spu)

    FILE* output_file = fopen("code_bin.bin", "wb");

    assert(output_file != NULL);

    fwrite(bin_buf, sizeof (int), j, output_file);

    fclose(output_file);

    #undef DEF_CMD
}

