#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

#include "Read_file.h"
#include "SPU_func.h"
#include "Assembler_func.h"


int Read_arg(struct Labels* labels,int code, int num_args, FILE* file, int* bin_buf, int pos, char* str)
{
    int arg = 0;
    char arg_str[SIZE_STR] = "";
    char simbol_a = 'a';

    switch(num_args)
    {
    case 1:
        *(bin_buf + pos) = code;
        switch (fscanf(file, "%d", &arg))
        {
        case READ_THE_NUMBER:
            pos = Push_to_bin_buf(bin_buf, pos, ARG_TYPE_INT, arg);
            break;

        case READ_THE_STR:
            fscanf(file, "%s", arg_str);

            if (strchr(arg_str,':') != NULL)
            {
                int label_val = Find_label(labels, bin_buf + pos, arg_str);
                pos = Push_to_bin_buf(bin_buf, pos, ARG_TYPE_INT, label_val);
            }
            else if (strchr(arg_str,'[') != NULL and strchr(arg_str,']') != NULL)
            {
                *(bin_buf + pos) += ARG_TYPE_TO_RAM;
                if (arg_str[1] == 'r' && arg_str[3] == 'x' && 'a' <= arg_str[2] && arg_str[2] <= 'd')
                {
                    pos = Push_to_bin_buf(bin_buf, pos, ARG_TYPE_STR, (int) (arg_str[2]) - (int) simbol_a);
                }
                else
                {
                    pos = Push_to_bin_buf(bin_buf, pos, ARG_TYPE_INT, atoi(arg_str + 1));
                }
            }
            else
            {
                pos = Push_to_bin_buf(bin_buf, pos, ARG_TYPE_STR, (int) (arg_str[1]) - (int) simbol_a);
            }
        }
        break;
    case 0:
        *(bin_buf + pos) = code;
        pos++;
        break;
    }
    return pos;
}


int Push_to_bin_buf(int* bin_buf, int position, int val_command, int arg)
{
    *(bin_buf + position) += val_command;
    *(bin_buf + position + 1) = arg;

    return position + 2;
}


int Put_label(struct Labels* labels, char* str, int position, int point)
{
    int len = strlen(str);
    char* point_ip = (char*) calloc(len + 1, sizeof (char));
    labels[point].point_name = strncpy(point_ip, str, len + 1);
    labels[point].ip = position;
    point++;

    return point;
}


int Find_label(struct Labels* labels, int* bin_buf, char* arg_str)
{
    int label_val = 0;
    for(int i = 0; i < NUM_OF_LABELS; i++)
    {
        if (!strncmp (labels[i].point_name, arg_str, min(sizeof arg_str, sizeof labels[i].point_name)))
        {
            label_val = labels[i].ip;
            break;
        }
    }
    return label_val;
}


int check_len_str (FILE* file)
{
    int len = 0;
    char input = 0;

    while ((input = fgetc(file)) == ' ')
        ;

    while ((input = fgetc(file)) != ' ')
    {
        len++;
        printf("%c\n", input);
    }
    printf("len = %d\n", len);
    return len + 1;
}


//________________________________________________________________________________________________________________
                                                                                // sdelay menche define


#define DEF_CMD(name, code, args, ...)                              \
    if (strcasecmp(str, #name) == 0)                                \
    {                                                               \
        switch(num_compil)                                          \
        {                                                           \
        case SECOND_COMPILATION:                                    \
            position = Read_arg(labels, code, args, file, bin_buf, position, str); \
            break;                                                  \
        case FIRST_COMPILATION:                                     \
            for (int i = 0; i < args; i++)                          \
            {                                                       \
                fscanf(file, "%s", str);                            \
            }                                                       \
            position = position + args + 1;                         \
            break;                                                  \
        }                                                           \
    }                                                               \
    else


//________________________________________________________________________________________________________________

int Compilate(struct Labels* labels,struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf)
{
    int point = 0;
    int position = 0;
    char str[SIZE_STR] = "";

    for (int i = 0; i < Num_rows + 1; i++)
    {
        //int len_str  = check_len_str(file);
        //char* str = (char*) calloc(len_str + 1, sizeof(char));

        fscanf(file, "%s", str);                                                //ду хаст  len check

        if (strchr(str,':') != NULL)                                            //print cheres
        {
            if(num_compil == FIRST_COMPILATION)
            {
            point = Put_label(labels, str, position, point);
            }
            continue;
        }

        /*
        switch (num_compil)
        {
        case SECOND_COMPILATION:
            #undef DEF_CMD
            #define DEF_CMD(name, code, args, ...)                              \
                if (strcasecmp(str, #name) == 0)                                \
                {                                                               \
                    j = Read_func(labels, code, args, file, bin_buf, j, str);   \
                }                                                               \
                else
            break;

        case FIRST_COMPILATION:
            #undef DEF_CMD
            #define DEF_CMD(name, code, args, ...)                              \
                if (strcasecmp(str, #name) == 0)                                \
                {                                                               \
                    for (int k = 0; k < args; k++)                              \
                    {                                                           \
                        fscanf(file, "%s", str);                                \
                    }                                                           \
                    j = j + args + 1;                                           \
                }                                                               \
                else
            break;
        }
        */
        #include "commands.h"

        /* else */ {
            spu -> SPU_err |= INCORRECT_COMAND;
            break;
        }

        if (spu -> SPU_err != 0)
        {
            SPU_DUMP(spu)
            printf("      |error command on %d str\n", i);
        }
        else
        {
        #ifdef SPU_DUMP_ON
            SPU_DUMP(spu)
            printf("      |now command on %d str\n", i);
        #endif
        }
    }

    return position;
}


