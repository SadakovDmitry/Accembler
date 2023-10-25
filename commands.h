#define DO_PUSH(val) Stack_Push(stk, val, canary);
#define DO_POP Stack_Pop(stk, &val, canary)
#define DO_POP_STK_CALLS Stack_Pop(stk_calls, &val, canary)
#define DO_PUSH_STK_CALLS(val) Stack_Push(stk_calls, val, canary);
//#define DO_PUSH_TO_RAM(val)
//    input*(spu -> RAM + val)

#define DO_JMP(name_jmp, code_jmp, args_jmp, symbol)        \
    DEF_CMD (name_jmp, code_jmp, args_jmp,                  \
    {                                                       \
        Elem_t val = 0;                                     \
        input_func = *(spu -> bin_buf + 1);                 \
        if(DO_POP symbol DO_POP)                            \
        {                                                   \
            spu -> bin_buf = start_buf + input_func - 2;    \
        }                                                   \
    })



#define accuracy 1

DEF_CMD (ZERO, 0, 0, {if (0) {}})

DEF_CMD (PUSH, 1, 1,
    {
    switch (func_num)
    {
    case 1 + ARG_TYPE_INT:
        input_func = *(spu -> bin_buf + 1);
        DO_PUSH(input_func * accuracy)
        break;
    case 1 + ARG_TYPE_TO_RAM:
        input_func = *(spu -> RAM + *(spu -> bin_buf + 1));
        DO_PUSH(input_func * accuracy)
        break;
    case 1 + ARG_TYPE_TO_RAM + ARG_TYPE_STR:
        input_func = spu -> args[input_func];
        input_func = *(spu -> RAM + input_func);
        DO_PUSH(input_func * accuracy)
        break;
    default:
        input_func = *(spu -> bin_buf + 1);
        input_func = spu -> args[input_func];
        DO_PUSH(input_func)
        break;
    }
    })

DEF_CMD (SUB , 2, 0,
    {
    Elem_t val = 0;
    Elem_t val1 = DO_POP;
    Elem_t val2 = DO_POP;
    DO_PUSH(val1 - val2)
    })

DEF_CMD (DIV , 3, 0,
    {
    Elem_t val = 0;
    Elem_t val1 = DO_POP;
    Elem_t val2 = DO_POP;
    DO_PUSH(val1 / (val2 / accuracy))
    })

DEF_CMD (OUT , 4, 0,
    {
    Elem_t val = 0;
    double Ret_val = (double) DO_POP / accuracy;
    printf("\n\tAnswer is: [\033[32m %lf \033[0m]\n", Ret_val);
    //getchar();
    })

DEF_CMD (ADD , 5, 0,
    {
    Elem_t val = 0;
    Elem_t val1 = DO_POP;
    Elem_t val2 = DO_POP;
    DO_PUSH(val1 + val2)
    })

DEF_CMD (MUL , 6, 0,
    {
    Elem_t val = 0;
    Elem_t val1 = DO_POP;
    Elem_t val2 = DO_POP;
    DO_PUSH(val1 * val2 / accuracy)
    })

DEF_CMD (SQRT, 7, 0,
    {
    Elem_t val = DO_POP * accuracy;
    if (val < 0)
    {
        spu -> SPU_err |= SQRT_FROM_INCORRECT_NUM;
        break;
    }
    DO_PUSH(sqrt(val)) // minus check
    })

DEF_CMD (SIN , 8, 0,
    {
    Elem_t val = 0;

    DO_PUSH((Elem_t) sin( (double) DO_POP / accuracy))
    })

DEF_CMD (COS , 9, 0,
    {
    Elem_t val = 0;

    DO_PUSH((Elem_t) cos( (double) DO_POP / accuracy))
    })

DEF_CMD (IN  , 10, 0,
    {
    double val = -3333333;
    printf("\n\033[33mPrint input value: \033[0m");
    //scanf(stack_t, &val);
    scanf("%lf", &val);

    while (val == -3333333)
    {
        Clean_buf();

        printf("\n\033[31mIncorrect input!!!\033[0m\n");
        printf("\n\033[33mPrint input value: \033[0m");
        //scanf(stack_t, &val);
        scanf("%lf", &val);
    }

    DO_PUSH((Elem_t) (val * accuracy))
    })

DEF_CMD (POP , 11, 1,
    {
    Elem_t val = 0;
    input_func = *(spu -> bin_buf + 1);

    switch (func_num)
    {
    case 11 + 128 + 32:
        *(spu -> RAM + *(spu -> args + input_func) / accuracy ) = DO_POP / accuracy;
        break;
    case 11 + 128 + 64:
        *(spu -> RAM + input_func) = DO_POP / accuracy;
        break;
    case 11 + 32:
        *(spu -> args + input_func) = DO_POP ;
        break;
    }
    })

DEF_CMD(HLT, -1, 0,
    {
    printf("\n\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[31mEND\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[0m\n");
    })

DEF_CMD(NOT, 12, 0,
    {
    Elem_t val = 0;

    DO_PUSH(DO_POP * -1)
    })

DEF_CMD(JMP, 13, 1,
    {
        input_func = *(spu -> bin_buf + 1);
        spu -> bin_buf = start_buf + input_func - 2;
    })

#include "jmp_commands.h"

DEF_CMD(RET, 21, 0,
    {
        Elem_t val = DO_POP_STK_CALLS;
        //printf("ret = %d", val);
        spu -> bin_buf = start_buf + val - 1;
    })

DEF_CMD(CALL, 22, 1,
    {
        Elem_t val = *(spu -> bin_buf + 1);
        //Elem_t val = spu -> bin_buf - start_buf + 2;
        DO_PUSH_STK_CALLS(spu -> bin_buf - start_buf + 2)
        //printf("call = %ld\n", spu -> bin_buf - start_buf + 2);
        spu -> bin_buf = start_buf + val - 2;
    })

DEF_CMD(THROW, 23, 0,
    {
        Elem_t val = 0;
        DO_POP;
    })

DEF_CMD(OUTC, 24, 0,
    {
        Elem_t val = 0;
        int Ret_val = (int) DO_POP / accuracy;
        printf("%c", (char) Ret_val);
    })

DEF_CMD (REM, 25, 0,
    {
    Elem_t val = 0;
    DO_PUSH(DO_POP % (DO_POP / accuracy))
    })
