#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Read_file.h"



const int MAX_NUM = 10000;



void fill_struct( struct About_text* ab_text, int* Num_rows, int size_of_text, char* buffer)
{
    assert(ab_text != NULL);

    ab_text -> rows = *Num_rows;
    ab_text -> text_size = size_of_text;
    ab_text -> id_buf = buffer;


    //printf(" Num_rows =  %d \n", ab_text -> rows);
}


int Size_of_text(int* Num_rows, FILE* file )
{
    //FILE* file = fopen(FILE_NAME, "r");

    assert ( file != NULL );
    int size_of_file = 0;
    char input = 0;

    while ((input = fgetc(file)) != EOF)
    {
        size_of_file++;

        if (input == '\n')
        {
            (*Num_rows)++;
        }
    }
    return size_of_file;
}


struct About_str* Input_text (int Num_rows, char* buffer, FILE* file) {

    assert(buffer != NULL);

    //FILE* file = fopen("Text_comands.txt", "r");

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

    int size_of_text = Size_of_text (Num_rows, file);
    buffer = (char*) calloc (size_of_text + 1, sizeof(char));

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
    else
    {
        printf("ERROR comand is not finded\n");
        return ZERO;
    }

}


void Make_file(struct About_text* ab_text, struct About_str* ab_str)
{
    assert(ab_text != NULL);
    assert(ab_str != NULL);

    FILE* output_file = fopen("Numbered_comands.txt", "a");

    assert(output_file != NULL);

    for (int i = 0; i < (ab_text ->rows); i++)
    {
        enum Comands num_of_comand = Convert_to_numbers(ab_str, ab_str[i].str, i);

        if (num_of_comand == 1)
        {
            fprintf(output_file, "%d", num_of_comand);
            fprintf(output_file, "%s",  ab_str[i].str + 4);
        }
        else
        {
            fprintf(output_file, "%d\n", num_of_comand);
        }

    }

    fputs("\n\n\n\n", output_file);

    fclose(output_file);
}


void Convert_to_cheak_file(struct About_text* ab_text, struct About_str* ab_str)
{
    assert(ab_text != NULL);
    assert(ab_str != NULL);

    FILE* output_file = fopen("Cheak_file.txt", "w");

    assert(output_file != NULL);

    for (int i = 0; i < (ab_text ->rows); i++)
    {
        Convert_to_comands(ab_str[i].str, output_file);
    }

    fputs("\n\n\n\n", output_file);

    fclose(output_file);

}


void Convert_to_comands(char* str, FILE* output_file)
{
    int func_num = 0;
    int input_func = 0;

    if (sscanf(str, "%d %d", &func_num, &input_func) == 2)
    {
        if (func_num == PUSH)
        {
            fprintf(output_file,"push %d\n", input_func);
        }
    }
    else
    {
        if (func_num == HLT)
        {
            fprintf(output_file,"hlt\n");
        }
        if (func_num == SUB)
        {
            fprintf(output_file,"sub\n");
        }
        if (func_num == DIV)
        {
            fprintf(output_file,"div\n");
        }
        if (func_num == ADD)
        {
            fprintf(output_file,"add\n");
        }
        if (func_num == MUL)
        {
            fprintf(output_file,"mul\n");
        }
        if (func_num == SQRT)
        {
            fprintf(output_file,"sqrt\n");
        }
        if (func_num == SIN)
        {
            fprintf(output_file,"sin\n");
        }
        if (func_num == COS)
        {
            fprintf(output_file,"cos\n");
        }
        if (func_num == IN)
        {
            fprintf(output_file,"in\n");
        }
        if (func_num == OUT)
        {
            fprintf(output_file,"out\n");
        }

    }
}