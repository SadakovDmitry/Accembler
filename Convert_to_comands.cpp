#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Read_file.h"



int main()
{
    struct About_text ab_text = {};
    struct SPU spu = {};
    ab_text.first_or_second_file = 2;

    FILE* file = fopen("code_bin.bin", "rb");

    spu.bin_buf = Work_with_bin_file(&ab_text, file);


    Convert_to_cheak_file(&ab_text, &spu);
}
