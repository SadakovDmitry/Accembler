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


#define DEF_CMD(name, code, num_args, program) \
    if (code == func_num)\
    {\
        switch (num_args)\
        {\
        case 2:\
            arg_type = *(spu -> bin_buf + 1);\
            \
            switch (arg_type)\
            {\
            case 2:\
                input_func = *(spu -> bin_buf + 2);\
                input_func = spu -> args[input_func];\
                \
                program\
                break;\
            case 1:\
                input_func = *(spu -> bin_buf + 2);\
                \
                if (input_func == NAN)\
                {\
                    printf("\n\033[31mIncorrect input!!!\033[0m\n");\
                    \
                }\
                \
                program\
                break;\
            default:\
                printf("\n\033[31mIncorrect input!!!\033[0m\n");\
            }\
            spu -> bin_buf = spu -> bin_buf + 3;\
            break;\
        case 1:\
            arg_type = *(spu -> bin_buf + 1);\
            \
            if (input_func != NAN)\
            {\
                program\
            }\
            else\
            {\
                printf("\n\033[31mIncorrect input!!!\033[0m\n");\
            }\
            spu -> bin_buf = spu -> bin_buf + 2;\
            break;\
        case 0:\
            program\
            spu -> bin_buf = spu -> bin_buf + 1;\
            break;\
        default:\
            printf("\n\033[31m1)Incorrect comand!!!\033[0m\n");\
        }\
    \
    }\



void Do_comands (struct About_text* ab_text, struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    assert(ab_text != NULL);
    assert(spu -> bin_buf != NULL);

    int func_num = 0;
    int arg_type = 0;
    int input_func = 0;

    while(func_num != CMD_HLT)
    {
        func_num = *(spu -> bin_buf);
        #include "commands.h"
    }
    #undef DEF_CMD
}
