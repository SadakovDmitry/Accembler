
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

#include "Read_file.h"
#include "SPU_func.h"


#undef DEF_CMD
#define DEF_CMD(name, num_of_comand, args, ...)\
    if (!strcasecmp( str, #name))\
    {\
        char simbol_a = 'a';\
        char arg[4] = "";\
        switch (args)\
        {\
        case 2:\
            fscanf(file, "%s", arg);\
            *(bin_buf + j) = num_of_comand;\
            \
            if (strncmp(arg, "rax", 3) == 0 || strncmp(arg, "rbx", 3) == 0 || strncmp(arg, "rcx", 3) == 0 || strncmp(arg, "rdx", 3) == 0)\
            {\
                *(bin_buf + j + 1) = 2;\
                *(bin_buf + j + 2) = (int) (arg[1]) - (int) simbol_a;\
            }\
            else\
            {\
                if (atoi(arg) == 0)\
                {\
                    spu.SPU_err |= INCORRECT_INPUT;\
                }\
                *(bin_buf + j + 1) = 1;\
                *(bin_buf + j + 2) = atoi(arg);\
            }\
            \
            j = j + 3;\
            \
            break;\
        case 1:\
            fscanf(file, "%s", arg);\
            if (!(strncmp(arg, "rax", 3) == 0 || strncmp(arg, "rbx", 3) == 0 || strncmp(arg, "rcx", 3) == 0 || strncmp(arg, "rdx", 3) == 0))\
                {\
                    spu.SPU_err |= INCORRECT_INPUT;\
                }\
            *(bin_buf + j) = num_of_comand;\
            *(bin_buf + j + 1) = (int) (arg[1]) - (int) simbol_a;\
            j = j + 2;\
            \
            break;\
        default:\
            *(bin_buf + j) = num_of_comand;\
            j++;\
        }\
    }\
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

    int* bin_buf = (int*) calloc (Num_rows * 3, sizeof(int));
    int j = 0;
    char str[5] = "";

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
    SPU_DUMP(&spu)

    FILE* output_file = fopen("code_bin.bin", "wb");

    assert(output_file != NULL);

    fwrite(bin_buf, sizeof (int), j, output_file);

    fclose(output_file);

    #undef DEF_CMD
}

