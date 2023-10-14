//#include "stack.h"
//#define DO_PUSH(val) Stack_Push(stk, val, canary)

//#define DO_POP  Stack_Pop(stk, &val, canary)

DEF_CMD (ZERO, 0, 0, {if (0) {}})

DEF_CMD (PUSH, 1, 2,
    {

    Stack_Push(stk, input_func, canary);

    })

DEF_CMD (SUB , 2, 0,
    {
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 - Ret_val1;

    Stack_Push(stk, val, canary);

    })

DEF_CMD (DIV , 3, 0,
    {
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 / Ret_val1;

    Stack_Push(stk, val, canary);
    })

DEF_CMD (OUT , 4, 0,
    {
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);
    printf("\n\tAnswer is: [\033[32m" stack_t "\033[0m]\n", Ret_val);
    })

DEF_CMD (ADD , 5, 0,
    {
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 + Ret_val1;

    Stack_Push(stk, val, canary);
    })

DEF_CMD (MUL , 6, 0,
    {
    Elem_t Ret_val1 = 0;
    Elem_t Ret_val2 = 0;

    Stack_Pop(stk, &Ret_val1, canary);
    Stack_Pop(stk, &Ret_val2, canary);

    Elem_t val = Ret_val2 * Ret_val1;

    Stack_Push(stk, val, canary);
    })

DEF_CMD (SQRT, 7, 0,
    {
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    Elem_t val = sqrt(Ret_val);

    Stack_Push(stk, val, canary);
    })

DEF_CMD (SIN , 8, 0,
    {
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    Elem_t val = (Elem_t) sin( (double) Ret_val);

    Stack_Push(stk, val, canary);
    })

DEF_CMD (COS , 9, 0,
    {
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    Elem_t val = (Elem_t) cos( (double) Ret_val);

    Stack_Push(stk, val, canary);
    })

DEF_CMD (IN  , 10, 0,
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
    })

DEF_CMD (POP , 11, 1,
    {
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);

    *(spu -> args + arg_type) = Ret_val;
    })

DEF_CMD (HLT, -1, 0,
    {
    printf("\n\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[31mEND\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[0m\n");
    //return -1;
    })


/*
DEF_CMD (ZERO, 0, 0, 0)

DEF_CMD (PUSH, 1, 2,
    {
    DO_PUSH(input_func);

    //return val;
    })

DEF_CMD (SUB , 2, 0,
    {
    Elem_t val = 0;
    Elem_t Ret_val1 = DO_POP;
    Elem_t Ret_val2 = DO_POP;

    DO_PUSH (Ret_val2 -  Ret_val1);

    //return val;
    })

DEF_CMD (DIV , 3, 0,
    {
    Elem_t val = 0;

    DO_PUSH (DO_POP / DO_POP );

    //return val;
    })

DEF_CMD (OUT , 4, 0,
    {
    Elem_t val = 0;

    DO_POP();

    printf("\n\tAnswer is: [\033[32m" stack_t "\033[0m]\n", val);

    //return Ret_val;
    })

DEF_CMD (ADD , 5, 0,
    {
    Elem_t val = 0;

    DO_PUSH (DO_POP + DO_POP );

    //return val;
    })

DEF_CMD (MUL , 6, 0,
    {
    Elem_t val = 0;

    DO_PUSH (DO_POP * DO_POP );

    //return val;
    })

DEF_CMD (SQRT, 7, 0,
    {
    Elem_t val = 0;

    DO_PUSH (sqrt(DO_POP) );

    //return val;
    })

DEF_CMD (SIN , 8, 0,
    {
    Elem_t val = 0;

    DO_PUSH ((Elem_t) sin( (double) DO_POP) );

    //return val;
    })

DEF_CMD (COS , 9, 0,
    {
    Elem_t val = 0;

    DO_PUSH ((Elem_t) cos( (double) DO_POP) );

    //return val;
    })

DEF_CMD (IN  , 10, 0,
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

    DO_PUSH(val);

    //return val;
    })

DEF_CMD (POP , 11, 1,
    {
    Elem_t Ret_val = 0;

    *(spu -> args + arg) = DO_POP;

    //return Ret_val;
    })

DEF_CMD (HLT, -1, 0,
    {
    printf("\n\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[31mEND\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[0m\n");
    return -1;
    })
*/
