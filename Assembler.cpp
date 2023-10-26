#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#include "Read_file.h"
#include "SPU_func.h"
#include "Assembler_func.h"

#undef DEF_CMD
#define assembler_file "Text_comands.txt" //"Square_eq.txt" "Text_comands.txt" "Factorial.txt"

int main()
{
    struct SPU spu = {};
    int Num_rows = 0;
    spu.SPU_err = 0;



    FILE* file = fopen (assembler_file, "r");

    assert(file != NULL);

    Size_of_text (&Num_rows, file);
    rewind (file);

    struct Labels* labels = (struct Labels*) calloc ( NUM_OF_LABELS, sizeof(struct Labels));
    int* bin_buf = (int*) calloc (Num_rows * 2, sizeof(int));

    //               Compilate (labels, &spu, Num_rows, FIRST_COMPILATION, file, bin_buf);
    First_compil(labels, Num_rows, file);
    rewind (file);
    //int size_buf =  Compilate (labels, &spu, Num_rows, SECOND_COMPILATION, file, bin_buf);
    int size_buf = Second_compil(labels, &spu, Num_rows, file, bin_buf);

    //Print_bin_buf(bin_buf, size_buf);

    fclose (file);



    FILE* output_file = fopen("code_bin.bin", "wb");

    assert (output_file != NULL);

    fwrite (bin_buf, sizeof (int), size_buf, output_file);

    fclose (output_file);

    #undef DEF_CMD
}

