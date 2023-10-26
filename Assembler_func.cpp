#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

#include "Read_file.h"
#include "SPU_func.h"
#include "Assembler_func.h"


int Read_arg(struct Labels* labels, struct SPU* spu, int code, int num_args, FILE* file, int* bin_buf, int pos)
{
    int arg = 0;
    char arg_str[SIZE_STR] = "";
    char simbol_a = 'a';

    *(bin_buf + pos) = code;

    switch(num_args)
    {
    case ONE_ARG:
        pos = Read_command_with_one_args( labels, spu, file, bin_buf, pos);
        break;

    case NO_ARGS:
        pos = Read_command_with_no_args(pos);
        break;
    }
    return pos;
}


int Read_command_with_no_args(int pos)
{
    pos++;

    return pos;
}


int Read_command_with_one_args(struct Labels* labels, struct SPU* spu, FILE* file, int* bin_buf, int pos)
{
    int arg = 0;
    char arg_str[SIZE_STR] = "";

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
            if (!Processing_arg(arg_str, bin_buf, &pos))
            {
                pos = Push_to_bin_buf(bin_buf, pos, ARG_TYPE_INT, atoi(arg_str + 1));
            }
        }
        else if (!Processing_arg(arg_str - 1, bin_buf, &pos))
        {
           spu -> SPU_err |= INCORRECT_INPUT;
        }
    }

    return pos;
}


int Processing_arg(char* arg_str, int* bin_buf, int* pos)
{
    if (arg_str[1] == 'r' && arg_str[3] == 'x' && 'a' <= arg_str[2] && arg_str[2] <= 'd')
    {
        *(pos) = Push_to_bin_buf(bin_buf, *(pos), ARG_TYPE_STR, (int) (arg_str[2]) - 'a');
        return 1;
    }
    else
    {
        return 0;
    }
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


void First_compil(struct Labels* labels, int Num_rows, FILE* file)
{
    int point = 0;
    int position = 0;
    char str[SIZE_STR] = "";

    for (int i = 0; i < Num_rows + 1; i++)
    {

        fscanf(file, "%s", str);

        if (strchr(str,':') != NULL)                                            //print cheres
        {
            point = Put_label(labels, str, position, point);
            continue;
        }

        #define DEF_CMD(name, code, args, ...)                              \
            if (strcasecmp(str, #name) == 0)                                \
            {                                                               \
                for (int i = 0; i < args; i++)                              \
                {                                                           \
                    fscanf(file, "%s", str);                                \
                }                                                           \
                position = position + args + 1;                             \
            }


        #include "commands.h"

        #undef DEF_CMD
    }
}


int Second_compil(struct Labels* labels,struct SPU* spu, int Num_rows, FILE* file, int* bin_buf)
{
    int point = 0;
    int position = 0;
    char str[SIZE_STR] = "";

    for (int i = 0; i < Num_rows + 1; i++)
    {

        fscanf(file, "%s", str);

        #define DEF_CMD(name, code, args, ...)                              \
            if (strcasecmp(str, #name) == 0)                                \
            {                                                               \
                position = Read_arg(labels, spu, code, args, file, bin_buf, position); \
            }                                                               \
            else

        if (strchr(str,':') == NULL)                                            //print cheres
        {
            #include "commands.h"

            /* else */ {
                spu -> SPU_err |= INCORRECT_COMAND;
                break;
            }
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
    #undef DEF_CMD

    return position;
}


//________________________________________________________________________________________________________________
/*
#define DEF_CMD(name, code, args, ...)                              \
    if (strcasecmp(str, #name) == 0)                                \
    {                                                               \
        switch(num_compil)                                          \
        {                                                           \
        case SECOND_COMPILATION:                                    \
            position = Read_arg(labels, spu, code, args, file, bin_buf, position); \
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
*/
//________________________________________________________________________________________________________________

/*
int Compilate(struct Labels* labels,struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf)
{
    int point = 0;
    int position = 0;
    char str[SIZE_STR] = "";

    for (int i = 0; i < Num_rows + 1; i++)
    {

        fscanf(file, "%s", str);

        if (strchr(str,':') != NULL)                                            //print cheres
        {
            if(num_compil == FIRST_COMPILATION)
            {
            point = Put_label(labels, str, position, point);
            }
            continue;
        }
        #include "commands.h"

         {
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
*/

