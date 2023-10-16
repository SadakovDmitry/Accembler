#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "SPU_func.h"
#include "stack.h"
#include "Read_file.h"


void SPU_Ctor(struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    assert(spu);

    spu -> args = (Elem_t*) calloc(NUM_ARGS, sizeof(Elem_t));

    assert(spu -> args);

    if (SPU_Verify(spu) != NO_ERROR)
    {
        SPU_DUMP(spu)
        #ifdef DUMP_ON
        STACK_DUMP(stk, canary)
        #endif
    }
    else
    {
        #ifdef SPU_DUMP_ON
        SPU_DUMP(spu)
        #endif
        #ifdef DUMP_ON
        STACK_DUMP(stk, canary)
        #endif
    }

}

void SPU_Dtor(struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    assert(spu);
    //spu -> args = NULL;

    if (SPU_Verify(spu) != NO_ERROR)
    {
        SPU_DUMP(spu)
        #ifdef DUMP_ON
        STACK_DUMP(stk, canary)
        #endif
    }
    else
    {
        #ifdef SPU_DUMP_ON
        SPU_DUMP(spu)
        #endif
        #ifdef DUMP_ON
        STACK_DUMP(stk, canary)
        #endif
    }
    free(spu -> args);
}

void SPU_Dump(struct SPU* spu, char* file , int line, const char* func)
{
    //assert(stk);
    //assert(canary);
    assert(spu);
    #ifdef SPU_DUMP_ON
    printf("\n\nSPU   |file: %s \n      |in: %d row \n      |function: %s \n", file, line, func);
    printf("      |\t\t    rax  |  rbx  |  rcx  |  rdx  |\n");
    printf("      |Arguments: ");
    #endif

    if (spu -> SPU_err & ARGS_NULL)
    {
        printf("\n\033[31mERROR\033[0m: pointer to ARGS = NULL!!!\n");
    }
    if (spu -> SPU_err & INCORRECT_INPUT)
    {
        printf("\n\033[31mERROR\033[0m: INCORRECT INPUT!!! \n");
    }
    if (spu -> SPU_err & INCORRECT_COMAND)
    {
        printf("\n\033[31mERROR\033[0m: INCORRECT COMAND!!! \n");
    }

    if (spu -> args != NULL)
    {
        for (int i = 0; i < NUM_ARGS; i++)
        {
            printf(stack_tt"   |", spu -> args[i]);
        }
    }


    printf("\n");
    /*
    #ifdef SPU_DUMP_ON
    STACK_DUMP(stk, canary)
    #endif
    */
}

unsigned int SPU_Verify(struct SPU* spu)
{
    spu -> SPU_err = NO_ERROR;

    if (spu -> args == NULL)
    {
        spu -> SPU_err |= ARGS_NULL;
    }


    return spu -> SPU_err;
}

/*
#define DEF_CMD(name, code, num_args, program) \
    printf("%d\n", func_num &= 1 << (code + 5));\
    if (func_num &= 1 << (code + 5))\
    {\
        printf("1)%s\n", #name);\
        if (func_num &= 1 << (code + 6))\
        {\
            input_func = *(spu -> bin_buf + 1);\
            program\
        }\
        else\
        {\
            input_func = *(spu -> bin_buf + 1);\
            input_func = spu -> args[input_func];\
            program\
        }\
        spu -> bin_buf = spu -> bin_buf + 2;\
    }\
    else if (code == func_num)\
    {\
        printf("2)%s\n", #name);\
        program\
        spu -> bin_buf = spu -> bin_buf + 1;\
    }\
*/

#define DEF_CMD(name, code, num_args, program) \
    if (func_num == int(1 << (code + 5)) + int(1 << (code + 6)) || func_num == int(1 << (code + 5)))\
    {\
        printf("1)%s\n", #name);\
        program\
        spu -> bin_buf = spu -> bin_buf + 2;\
    }\
    else if (code == func_num)\
    {\
        printf("2)%s\n", #name);\
        program\
        spu -> bin_buf = spu -> bin_buf + 1;\
    }\


void Do_comands (struct About_text* ab_text, struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    assert(ab_text != NULL);
    assert(spu -> bin_buf != NULL);

    int func_num = 0;
    int input_func = 0;
    int* start_buf = spu -> bin_buf;

    while(func_num != CMD_HLT)
    {
        SPU_DUMP(spu)
        func_num = *(spu -> bin_buf);
        #include "commands.h"
        /*else*/

    }
    SPU_DUMP(spu)

    #undef DEF_CMD
}

