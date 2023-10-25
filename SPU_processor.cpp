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

    spu.RAM = (Elem_t*) calloc (SIZE_OF_RAM, sizeof(Elem_t));



    FILE* file = fopen("code_bin.bin", "rb");

    spu.bin_buf = Work_with_bin_file(&ab_text, file);

    //Print_bin_buf(spu.bin_buf, ab_text.text_size);

    struct Stack* stk = Stack_Ctor( capacity, &ERR, &canary);
    struct Stack* stk_calls = Stack_Calls_Ctor( capacity, &ERR, &canary);

    SPU_Ctor (stk, &canary, &spu);

    Do_comands (&ab_text, stk, stk_calls, &canary, &spu);

    SPU_Dtor (stk, &canary, &spu);

    Stack_Dtor (stk, &canary);
    Stack_Dtor (stk_calls, &canary);

    Print_RAM (&spu, SIZE_OF_RAM);

    Print_VRAM(&spu, SIZE_OF_RAM);

}
