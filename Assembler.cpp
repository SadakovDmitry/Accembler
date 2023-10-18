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

int main()
{
    struct SPU spu = {};
    int Num_rows = 0;
    spu.SPU_err = 0;

    FILE* file = fopen("Text_comands.txt", "r");

    assert(file != NULL);

    Size_of_text(&Num_rows, file);
    rewind(file);

    struct Labels* labels = (struct Labels*) calloc ( NUM_OF_LABELS, sizeof(struct Labels));
    int* bin_buf = (int*) calloc (Num_rows * 10, sizeof(int));

            Compilate(labels, &spu, Num_rows, 1, file, bin_buf);
    rewind(file);
    int j = Compilate(labels, &spu, Num_rows, 2, file, bin_buf);

    for (int i = 0; i < j; i++)
    {
        printf("%d ", *(bin_buf + i));
    }

    //SPU_DUMP(&spu)

    fclose(file);


    FILE* output_file = fopen("code_bin.bin", "wb");

    assert(output_file != NULL);

    fwrite(bin_buf, sizeof (int), j, output_file);

    fclose(output_file);

    #undef DEF_CMD
}

