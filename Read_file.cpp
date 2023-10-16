#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "Read_file.h"
//#include "enum_commands.h"



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



#define DEF_CMD(name, code , args, ...)\
    if(func_num == code)\
    {\
        switch(args)\
        {\
        case 2:\
            arg_type = *(spu -> bin_buf + 1);\
            input_func = *(spu -> bin_buf + 2);\
            \
            switch(arg_type)\
            {\
            case 1:\
                fprintf(output_file,"PUSH %d\n", input_func);\
                break;\
            case 2:\
                fprintf(output_file,"PUSH r%cx\n", (char)((int)simbol_a + input_func));\
                break;\
            }\
            spu -> bin_buf = spu -> bin_buf + 3;\
            break;\
        case 1:\
            input_func = *(spu -> bin_buf + 1);\
            fprintf(output_file,"POP r%cx\n", (char)((int)simbol_a + input_func));\
            spu -> bin_buf = spu -> bin_buf + 2;\
            break;\
        case 0:\
            fprintf(output_file, #name"\n");\
            spu -> bin_buf = spu -> bin_buf + 1;\
            break;\
        }\
    }



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
    char str[5] = "";

    while(func_num != CMD_HLT)
    {
        func_num = *(spu -> bin_buf);
        #include "commands.h"
    }

    fclose(output_file);
    #undef DEF_CMD
}




