#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "Read_file.h"



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
        //size_of_file++;

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




enum Comands Convert_to_numbers(struct About_str* ab_str, char * now_comand, int i )
{

    if (strncmp(ab_str[i].str, "push", 4) == 0)
    {
        return PUSH;
    }
    if (strncmp(ab_str[i].str, "sub", 3) == 0)
    {
        return SUB;
    }
    if (strncmp(ab_str[i].str, "div", 3) == 0)
    {
        return DIV;
    }
    if (strncmp(ab_str[i].str, "out", 3) == 0)
    {
        return OUT;
    }
    if (strncmp(ab_str[i].str, "add", 3) == 0)
    {
        return ADD;
    }
    if (strncmp(ab_str[i].str, "mul", 3) == 0)
    {
        return MUL;
    }
    if (strncmp(ab_str[i].str, "sqrt", 4) == 0)
    {
        return SQRT;
    }
    if (strncmp(ab_str[i].str, "sin", 3) == 0)
    {
        return SIN;
    }
    if (strncmp(ab_str[i].str, "cos", 3) == 0)
    {
        return COS;
    }
    if (strncmp(ab_str[i].str, "in", 2) == 0)
    {
        return IN;
    }
    if (strncmp(ab_str[i].str, "hlt", 3) == 0)
    {
        return HLT;
    }
    if (strncmp(ab_str[i].str, "pop", 3) == 0)
    {
        return POP;
    }
    else
    {
        printf("ERROR comand is not finded\n");
        return ZERO;
    }

}


void Make_bin_file(struct About_text* ab_text, struct About_str* ab_str)
{
    assert(ab_text != NULL);
    assert(ab_str != NULL);

    FILE* output_file = fopen("code_bin.bin", "wb");

    assert(output_file != NULL);

    int* bin_buf = (int*) calloc (ab_text -> text_size + 1, sizeof(int));
    int j = 0;

    for (int i = 0; i < (ab_text ->rows); i++)
    {
        int num_of_comand = (int) Convert_to_numbers(ab_str, ab_str[i].str, i);
        char simbol = 'a';

        switch (num_of_comand)
        {
        case 1:
            *(bin_buf + j) = num_of_comand;


            if (strncmp(ab_str[i].str + 5, "rax", 3) == 0 || strncmp(ab_str[i].str + 5, "rbx", 3) == 0 || strncmp(ab_str[i].str + 5, "rcx", 3) == 0 || strncmp(ab_str[i].str + 5, "rdx", 3) == 0)
            {
                *(bin_buf + j + 1) = 2;
                *(bin_buf + j + 2) = (int) (*(ab_str[i].str + 6)) - (int) simbol;
            }
            else
            {
                *(bin_buf + j + 1) = 1;
                *(bin_buf + j + 2) = atoi(ab_str[i].str + 5);
            }

            j = j + 3;

            break;
        case 11:
            *(bin_buf + j) = num_of_comand;
            *(bin_buf + j + 1) = (int) (*(ab_str[i].str + 5)) - (int)simbol;
            j = j + 2;

            break;
        default:
            *(bin_buf + j) = num_of_comand;
            j++;
        }

    }

    fwrite(bin_buf, sizeof (int), j, output_file);
    fclose(output_file);
}


void Convert_to_cheak_file(struct About_text* ab_text, struct SPU* spu)
{
    assert(ab_text != NULL);
    assert(spu -> bin_buf != NULL);

    FILE* output_file = fopen("Cheak_file.txt", "w");

    assert(output_file != NULL);

    while(true)
    {
        if (Convert_to_comands(spu, output_file) == -1)
        {
            break;
        }
    }

    fclose(output_file);

}


int Convert_to_comands(struct SPU* spu, FILE* output_file)
{
    int func_num = 0;
    int arg_type = 0;
    int input_func = 0;
    int simbol_a = 'a';

    func_num = *(spu -> bin_buf);

    if (func_num == PUSH)
    {
        func_num = *(spu -> bin_buf);
        arg_type = *(spu -> bin_buf + 1);
        input_func = *(spu -> bin_buf + 2);

        switch (arg_type)
        {
        case 1:
            fprintf(output_file,"push %d\n", input_func);
            break;
        case 2:
            fprintf(output_file,"push r%cx\n", (char)((int)simbol_a + input_func));
            break;
        }
        spu -> bin_buf = spu -> bin_buf + 3;
    }
    else if (func_num == POP)
    {
        input_func = *(spu -> bin_buf + 1);
        fprintf(output_file,"pop r%cx\n", (char)((int)simbol_a + input_func));
        spu -> bin_buf = spu -> bin_buf + 2;
    }
    else
    {
        switch(func_num)
        {
        case HLT:
            fprintf(output_file,"hlt\n");
            return -1;
            break;
        case SUB:
            fprintf(output_file,"sub\n");
            break;
        case DIV:
            fprintf(output_file,"div\n");
            break;
        case ADD:
            fprintf(output_file,"add\n");
            break;
        case MUL:
            fprintf(output_file,"mul\n");
            break;
        case SQRT:
            fprintf(output_file,"sqrt\n");
            break;
        case COS:
            fprintf(output_file,"cos\n");
            break;
        case SIN:
            fprintf(output_file,"sin\n");
            break;
        case IN:
            fprintf(output_file,"in\n");
            break;
        case OUT:
            fprintf(output_file,"out\n");
            break;
        default:
            printf("\n\033[31mIncorrect comand!!!\033[0m\n");
            break;
        }
        spu -> bin_buf = spu -> bin_buf + 1;
    }
    return 1;
}


