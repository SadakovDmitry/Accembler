
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#include "Read_file.h"
#include "SPU_func.h"

#undef DEF_CMD

#define max(a, b) (((a) < (b)) ? (a) : (b))

const int mask_push_reg = 0x60000000;
int Read_func(struct Labels* labels,int code, int args, FILE* file, int* bin_buf, int j, char* str);
int Compilate(struct Labels* labels, struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf);


int Read_func(struct Labels* labels,int code, int args, FILE* file, int* bin_buf, int j, char* str)
{
    int arg = 0;
    char arg_str[10] = "";
    char simbol_a = 'a';

    switch(args)
    {
    case 1:
        switch (fscanf(file, "%d", &arg))
        {
        case 1:
            *(bin_buf + j) |= 1 << (code + 5);
            *(bin_buf + j) |= 1 << (code + 6);
            *(bin_buf + j + 1) = arg;
            break;
        case 0:
            fscanf(file, "%s", arg_str);
            *(bin_buf + j) |= 1 << (code + 5);

            if (strchr(arg_str,':') != NULL)
            {
                printf("--------------OK\n");
                for(int k = 0; k < 10; k++)
                {
                    printf("oh\n");
                    if (strncmp(labels[k].point_name, arg_str, max(strlen(str), strlen(labels[k].point_name))) == 0)
                    {
                    *(bin_buf + j + 1) = labels[k].ip;
                    printf("---------in def : point = %s, ip = %d\n", labels[k].point_name, labels[k].ip);
                    break;
                    }
                }
                *(bin_buf + j) |= 1 << (code + 6);
            }
            else
            {
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

#define DEF_CMD(name, code, args, ...)                              \
    if (strchr(str,':') != NULL)                                    \
    {                                                               \
        if(num_compil == 1)                                         \
        {                                                           \
        int len = strlen(str);                                      \
        char* point_ip = (char*) calloc(len + 1, sizeof (char));    \
        labels[point].point_name = strncpy(point_ip, str, len);     \
        labels[point].ip = j;                                       \
        printf("j = %d\npointer = %d\n", j, point);                 \
        printf("--in def : point = %s, ip = %d\n", labels[point].point_name, labels[point].ip);\
        point++;                                                    \
        }                                                           \
    }                                                               \
    else if (strcasecmp(str, #name) == 0)                           \
    {                                                               \
        switch(num_compil)                                          \
        {                                                           \
        case 2:                                                     \
            printf("2) j = %d\n", j);                               \
            printf("str = %s\n", str);                              \
            printf("==in def : point = %s, ip = %d\n", labels[0].point_name, labels[0].ip);\
            printf("==in def : point = %s, ip = %d\n", labels[1].point_name, labels[1].ip);\
            j = Read_func(labels, code, args, file, bin_buf, j, str);\
            printf("2) j = %d\n", j);                               \
            break;                                                  \
        case 1:                                                     \
            for (int k = 0; k < args; k++)                          \
            {                                                       \
                fscanf(file, "%s", str);                            \
            }                                                       \
            j = j + args + 1;                                       \
            printf("//in def : point = %s, ip = %d\n", labels[0].point_name, labels[0].ip);\
            printf("//in def : point = %s, ip = %d\n", labels[1].point_name, labels[1].ip);\
                                                                    \
            printf("1)%s j = %d\n", #name,  j);                     \
            break;                                                  \
        }                                                           \
    }                                                               \
    else



int Compilate(struct Labels* labels,struct SPU* spu, int Num_rows, int num_compil, FILE* file, int* bin_buf)
{
    int point = 0;
    int j = 0;
    char str[10] = "";

    for (int i = 0; i < Num_rows + 1; i++)
    {
        printf("<>\n");
        printf("in def : point = %s, ip = %d\n", labels[0].point_name, labels[0].ip);
        printf("in def : point = %s, ip = %d\n", labels[1].point_name, labels[1].ip);
        fscanf(file, "%s", str);
        #include "commands.h"
        /*else*/
        {
            spu -> SPU_err |= INCORRECT_COMAND;
            printf("suka \n");
            break;
        }
    }
    return j;
}

/*
#define DEF_CMD(name, code, args, ...)                              \
    if (strchr(str,':') != NULL)                                    \
    {                                                               \
        labels[point].point_name = str;                             \
        labels[point].ip = j;                                       \
        point++;                                                    \
    }                                                               \
    else if (strcasecmp(str, #name) == 0)                           \
    {                                                               \
        j = j + args + 1;                                           \
    }                                                               \
    else
*/





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
    printf("size = %lu\n", sizeof(struct Labels));
    struct Labels* labels = (struct Labels*) calloc (10, sizeof(struct Labels));
    //int point = 0;

    int* bin_buf = (int*) calloc (Num_rows * 10, sizeof(int));
    //int j = 0;
    //char str[5] = "";
    printf("-------------------------------------------------------------------------------------\n");
            Compilate(labels, &spu, Num_rows, 1, file, bin_buf);
    printf("-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < 10; i++)
    {
        printf("point = %s, ip = %d\n", labels[i].point_name, labels[i].ip);
    }
    printf("-------------------------------------------------------------------------------------\n");
    rewind(file);

    int j = Compilate(labels, &spu, Num_rows, 2, file, bin_buf);

    printf("-------------------------------------------------------------------------------------\n");

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

