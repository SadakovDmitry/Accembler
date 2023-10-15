#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Read_file.h"
#include "stack.h"

#define SPU_DUMP(stk, canary, spu) SPU_Dump(stk, canary, spu, (char*)__FILE__, __LINE__, __func__);
#define NUM_ARGS 4

enum SPU_ERR : unsigned int
{
    ARGS_NULL = 1 << 0
};
/*
Elem_t hlt ();
Elem_t push (struct Stack* stk, struct Canary* canary, char* str);
Elem_t sub (struct Stack* stk, struct Canary* canary);
Elem_t div (struct Stack* stk, struct Canary* canary);
Elem_t out (struct Stack* stk, struct Canary* canary);
Elem_t add (struct Stack* stk, struct Canary* canary);
Elem_t mul (struct Stack* stk, struct Canary* canary);
Elem_t sqrt (struct Stack* stk, struct Canary* canary);
Elem_t sinus (struct Stack* stk, struct Canary* canary);
Elem_t cosinus (struct Stack* stk, struct Canary* canary);
Elem_t in (struct Stack* stk, struct Canary* canary);
Elem_t pop (struct Stack* stk, struct Canary* canary, struct SPU* spu, char* arg);
*/
//Elem_t Choose_comand(struct Stack* stk, struct Canary* canary, char* str, struct SPU* spu);
void Do_comands (struct About_text* ab_text, struct About_str* ab_str, struct Stack* stk, struct Canary* canary, struct SPU* spu);

unsigned int SPU_Verify(struct SPU* spu);
void SPU_Dump(struct Stack* stk, struct Canary* canary, struct SPU* spu, char* file , int line, const char* func);
void SPU_Dtor(struct Stack* stk, struct Canary* canary, struct SPU* spu);
void SPU_Ctor(struct Stack* stk, struct Canary* canary, struct SPU* spu);

/*
Elem_t hlt ()
{
    printf("\n\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[31mEND\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[0m\n");
    return CMD_HLT;
}

Elem_t push (struct Stack* stk, struct Canary* canary, Elem_t val)
{
    Stack_Push(stk, val, canary);

    return val;
}

Elem_t sub (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 - Ret_val1;

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t div (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 / Ret_val1;

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t out (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);
    printf("\n\tAnswer is: [\033[32m" stack_t "\033[0m]\n", Ret_val);

    return Ret_val;
}

Elem_t add (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 + Ret_val1;

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t mul (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 * Ret_val1;

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t sqrt (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    Elem_t val = sqrt(Ret_val);

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t sinus (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    Elem_t val = (Elem_t) sin( (double) Ret_val);

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t cosinus (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    Elem_t val = (Elem_t) cos( (double) Ret_val);

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t in (struct Stack* stk, struct Canary* canary)
{
    Elem_t val = -3333333;
    printf("\n\033[33mPrint input value:\033[0m");
    scanf(stack_t, &val);

    while (val == -3333333)
    {
        Clean_buf();

        printf("\n\033[31mIncorrect input!!!\033[0m\n");
        printf("\n\033[33mPrint input value:\033[0m");
        scanf(stack_t, &val);
    }

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t pop (struct Stack* stk, struct Canary* canary, struct SPU* spu, int arg)
{
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    *(spu -> args + arg) = Ret_val;

    return Ret_val;
}
*/



void SPU_Ctor(struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    assert(spu);

    spu -> args = (Elem_t*) calloc(NUM_ARGS, sizeof(Elem_t));

    assert(spu -> args);

    if (SPU_Verify(spu) != NO_ERROR)
    {
        SPU_DUMP(stk, canary, spu)
    }
    else
    {
        #ifdef SPU_DUMP_ON
        SPU_DUMP(stk, canary, spu)
        #endif
    }

}

void SPU_Dtor(struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    assert(spu);
    //spu -> args = NULL;

    if (SPU_Verify(spu) != NO_ERROR)
    {
        SPU_DUMP(stk, canary, spu)
    }
    else
    {
        #ifdef SPU_DUMP_ON
        SPU_DUMP(stk, canary, spu)
        #endif
    }
    free(spu -> args);
}

void SPU_Dump(struct Stack* stk, struct Canary* canary, struct SPU* spu, char* file , int line, const char* func)
{
    assert(stk);
    assert(canary);
    assert(spu);

    printf("\n\nSPU   |file: %s \n      |in: %d row \n      |function: %s \n", file, line, func);
    printf("      |\t\t    rax  |  rbx  |  rcx  |  rdx  |\n");
    printf("      |Arguments: ");

    if (spu -> SPU_err & ARGS_NULL)
    {
        printf("\n\033[31mERROR\033[0m: pointer to ARGS = NULL!!!\n");
    }

    if (spu -> args != NULL)
    {
        for (int i = 0; i < NUM_ARGS; i++)
        {
            printf("%4d   |", spu -> args[i]);
        }
    }

    printf("\n");
    #ifdef SPU_DUMP_ON
    STACK_DUMP(stk, canary)
    #endif
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



/*
Elem_t Choose_comand(struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    int func_num = 0;
    int arg_type = 0;
    int input_func = 0;
    int i = 0;

    func_num = *(spu -> bin_buf);

    if (func_num == 1)
    {
        arg_type = *(spu -> bin_buf + 1);

        switch (arg_type)
        {
        case 2:
            input_func = *(spu -> bin_buf + 2);

            push(stk, canary, spu -> args[input_func]);
            break;
        case 1:
            input_func = *(spu -> bin_buf + 2);

            if (input_func == NAN)
            {
                printf("\n\033[31mIncorrect input!!!\033[0m\n");

                return -1;
            }

            push(stk, canary, input_func);
            break;
        default:
            printf("\n\033[31mIncorrect input!!!\033[0m\n");
        }

        spu -> bin_buf = spu -> bin_buf + 3;                                                                       //
    }

    else if (func_num == 11)
    {
        input_func = *(spu -> bin_buf + 1);

        if (input_func != NAN)
        {
            pop(stk, canary, spu, input_func);
        }
        else
        {
            printf("\n\033[31mIncorrect input!!!\033[0m\n");
        }
        spu -> bin_buf = spu -> bin_buf + 2;
    }
    else
    {
        switch (func_num)
        {
        case CMD_HLT:
            hlt ();
            return CMD_HLT;
            break;
        case CMD_SUB:
            sub (stk, canary);
            break;
        case CMD_DIV:
            div (stk, canary);
            break;
        case CMD_ADD:
            add (stk, canary);
            break;
        case CMD_MUL:
            mul (stk, canary);
            break;
        case CMD_SQRT:
            sqrt (stk, canary);
            break;
        case CMD_COS:
            cosinus (stk, canary);
            break;
        case CMD_SIN:
            sinus (stk, canary);
            break;
        case CMD_IN:
            in (stk, canary);
            break;
        case CMD_OUT:
            out (stk, canary);
            break;
        case CMD_POP:
            pop (stk, canary, spu, input_func);
        case CMD_PUSH:
            printf("\n\033[31mIncorrect input!!!\033[0m\n");
            return -1;
        default:
            printf("\n\033[31mIncorrect comand!!!\033[0m\n");
            return -1;
            break;
        }
        spu -> bin_buf = spu -> bin_buf + 1;
    }

    #ifdef SPU_DUMP_ON
        SPU_DUMP(stk, canary, spu)
    #endif

    return CMD_ZERO;
}

void Do_comands (struct About_text* ab_text, struct Stack* stk, struct Canary* canary, struct SPU* spu)
{
    assert(ab_text != NULL);
    assert(spu -> bin_buf != NULL);

    while(true)
    {
        if (Choose_comand(stk, canary, spu) == -1)
        {
            break;
        }
    }
}
*/
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
}


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
    /*
    for (int i = 0; i < ab_text.text_size; i++)
    {
        printf("%d ", *(spu.bin_buf + i));
    }
    */

    struct Stack* stk = Stack_Ctor( capacity, &ERR, &canary);

    SPU_Ctor(stk, &canary, &spu);

    Do_comands (&ab_text, stk, &canary, &spu);

    SPU_Dtor(stk, &canary, &spu);
    Stack_Dtor(stk, &canary);
    #undef DEF_CMD
}
