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
}
