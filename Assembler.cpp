#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Read_file.h"


int main()
{

    struct About_text ab_text = {};
    char* buffer = NULL;
    int Num_rows = 0;
    ab_text.first_or_second_file = 1;

    FILE* output_file = fopen("Numbered_comands.txt", "w");
    fclose(output_file);

    FILE* file = fopen("Text_comands.txt", "r");

    struct About_str* ab_str = Work_with_input_file(&ab_text, buffer, &Num_rows, file);

    Make_file(&ab_text, ab_str);

    /*
    FILE *code_file1 = fopen("code_bin.bin", "rb");
    char* binfile = (char*) calloc(100, sizeof(unsigned long));
    int lenfile = fread(binfile, 8, 100, code_file1);
    printf("\n%s\n", binfile);

    FILE *code_file1 = fopen("code_bin.bin", "rb");
    char* binfile = (char*) calloc(100, sizeof(unsigned long));

    int lenfile = fread(binfile, 4, 100, code_file1);
    printf("%d\n", lenfile);
    printf("binfile:\n%s", binfile);
    fclose(code_file1);

    FILE *code_file2 = fopen("code_bin.bin", "wb");

    //for(int i = 0; i < lenfile; i++)
    //{
    //fwrite(binfile, sizeof (unsigned long), 8, code_file2);
    char null = '0';

    for(int i = 0; i < lenfile + 32; i++)
    {
        if (*(binfile + i) != ' ' && *(binfile + i) != '\n')
        {
            printf( "%u\n", (int) *(binfile + i) - (int) (null) );
            fprintf(code_file2, "%08X\n", (int) *(binfile + i) - (int) (null));
        }
    }
    //}

    fclose(code_file2);
    free(binfile);

    printf("\n\n\n\n\n");
    for(int i = 0; i < 255; i++)
    {
        printf("%d = <%c>\n", i, i);
    }
    */
}


