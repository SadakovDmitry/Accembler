#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "SPU_func.h"
#include "stack.h"
#include "Read_file.h"
#include "Assembler_func.h"


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
    assert(spu);

    printf("\n\nSPU   |file: %s \n      |in: %d row \n      |function: %s \n", file, line, func);
    printf("      |\t\t    rax  |  rbx  |  rcx  |  rdx  |\n");
    printf("      |Arguments: ");
    //printf("      |now comand : push 1 pop rax  push 11 push rax ja Stop: push rax push rax mul out push rax push 1 add pop rax jmp Next: hlt);


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
        printf("\n\033[31mERROR\033[0m: INCORRECT COMMAND!!! \n");
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

//func_num & (UINT32_MAX ^ (128 | 64 | 32))

#define DEF_CMD(name, code, num_args, program) \
    if (func_num == (code | 128 | 64) || func_num == (code | 128 | 32) || func_num == (code | 64) || func_num == (code | 32) || func_num == code)\
    {\
        program\
        spu -> bin_buf = spu -> bin_buf + num_args + 1;\
    }\
    else


void Do_comands (struct About_text* ab_text, struct Stack* stk, struct Stack* stk_calls, struct Canary* canary, struct SPU* spu)
{
    assert(ab_text != NULL);
    assert(spu -> bin_buf != NULL);

    int func_num = 0;
    int input_func = 0;
    int* start_buf = spu -> bin_buf;
    //char* name_func = (char*) calloc (10, sizeof(char));

    while(func_num != CMD_HLT)
    {
        func_num = *(spu -> bin_buf);
        #include "commands.h"
        /*else*/
        {
            spu -> SPU_err |= INCORRECT_COMAND;
            break;
        }

        if (spu -> SPU_err != 0)
        {
            SPU_DUMP(spu)
            printf("      |now command : %ld\n", (spu -> bin_buf - start_buf));
        }
        else
        {
        #ifdef SPU_DUMP_ON
            SPU_DUMP(spu)
            printf("      |now command : %ld\n",( spu -> bin_buf - start_buf));
        #endif
        }
        //Print_VRAM(spu, SIZE_OF_RAM);
        //printf("\n\n\n");
        //getchar();
    }

    #undef DEF_CMD
}

