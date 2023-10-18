#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Read_file.h"
#include "stack.h"
#include "SPU_func.h"


int main()
{
    struct Canary canary = {};
    struct About_str ab_str = {};
    struct About_text ab_text = {};
    struct ERRORS ERR = {};
    struct SPU spu = {};
    char* buffer = NULL;
    int Num_rows = 0;
    int capacity = 1;
    ab_text.first_or_second_file = 2;



    FILE* file = fopen("code_bin.bin", "rb");

    spu.bin_buf = Work_with_bin_file(&ab_text, file);

    for (int i = 0; i < ab_text.text_size; i++)
    {
        printf("%d ", *(spu.bin_buf + i));
    }


    struct Stack* stk = Stack_Ctor( capacity, &ERR, &canary);

    SPU_Ctor(stk, &canary, &spu);

    Do_comands (&ab_text, stk, &canary, &spu);

    SPU_Dtor(stk, &canary, &spu);
    Stack_Dtor(stk, &canary);

}
