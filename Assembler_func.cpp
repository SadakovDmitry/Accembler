#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

#include "Read_file.h"
#include "SPU_func.h"
#include "Assembler_func.h"


int Read_func(struct Labels* labels,int code, int args, FILE* file, int* bin_buf, int j, char* str)
{
    int arg = 0;
    char arg_str[10] = "";
    char simbol_a = 'a';

    switch(args)
    {
    case 1:
        *(bin_buf + j) = code;
        switch (fscanf(file, "%d", &arg))
        {
        case READ_THE_NUMBER:
            *(bin_buf + j) += ARG_TYPE_INT;
            *(bin_buf + j + 1) = arg;
            break;
        case READ_THE_STR:
            fscanf(file, "%s", arg_str);

            if (strchr(arg_str,':') != NULL)
            {
                for(int k = 0; k < NUM_OF_LABELS; k++)
                {
                    if (!strncmp (labels[k].point_name, arg_str, max(strlen (str), strlen (labels[k].point_name))))
                    {
                    *(bin_buf + j + 1) = labels[k].ip;
                    break;
                    }
                }
                *(bin_buf + j) += ARG_TYPE_INT;
            }
            else
            {
                *(bin_buf + j) += ARG_TYPE_STR;
                *(bin_buf + j + 1) = (int) (arg_str[1]) - (int) simbol_a;
            }
        }
        j = j + 2;
        break;
    case 0:
        *(bin_buf + j) = code;
        j++;
        break;
    }
    return j;
}

//________________________________________________________________________________________________________________

#define DEF_CMD(name, code, args, ...)                              \
    if (strchr(str,':') != NULL)                                    \
    {                                                               \
        if(num_compil == FIRST_COMPILATION)                         \
        {                                                           \
        int len = strlen(str);                                      \
        char* point_ip = (char*) calloc(len + 1, sizeof (char));    \
        labels[point].point_name = strncpy(point_ip, str, len + 1); \
        labels[point].ip = j;                                       \
        point++;                                                    \
        }                                                           \
    }                                                               \
    else if (strcasecmp(str, #name) == 0)                           \
    {                                                               \
        switch(num_compil)                                          \
        {                                                           \
        case SECOND_COMPILATION:                                    \
            j = Read_func(labels, code, args, file, bin_buf, j, str);\
            break;                                                  \
        case FIRST_COMPILATION:                                     \
            for (int k = 0; k < args; k++)                          \
            {                                                       \
                fscanf(file, "%s", str);                            \
            }                                                       \
            j = j + args + 1;                                       \
            break;                                                  \
        }                                                           \
    }                                                               \
    else

//________________________________________________________________________________________________________________

int Compilate(struct Labels* labels,struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf)
{
    int point = 0;
    int j = 0;
    char str[10] = "";

    for (int i = 0; i < Num_rows + 1; i++)
    {
        fscanf(file, "%s", str);
        #include "commands.h"

        {
            spu -> SPU_err |= INCORRECT_COMAND;
            break;
        }
    }
    if (spu -> SPU_err != 0)
    {
        SPU_DUMP(spu)
    }
    return j;
}


