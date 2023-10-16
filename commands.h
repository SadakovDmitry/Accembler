#define DO_PUSH(val) Stack_Push(stk, val, canary);

#define DO_POP Stack_Pop(stk, &val, canary)

#define accuracy 1000

DEF_CMD (ZERO, 0, 0, {if (0) {}})

DEF_CMD (PUSH, 1, 2,
    {
    DO_PUSH(input_func * accuracy)
    })

DEF_CMD (SUB , 2, 0,
    {
    Elem_t val = 0;
    DO_PUSH(DO_POP - DO_POP)
    })

DEF_CMD (DIV , 3, 0,
    {
    Elem_t val = 0;
    DO_PUSH(DO_POP / (DO_POP / accuracy))
    })

DEF_CMD (OUT , 4, 0,
    {
    Elem_t val = 0;
    double Ret_val = (double) DO_POP / accuracy;
    printf("\n\tAnswer is: [\033[32m %lf \033[0m]\n", Ret_val);
    })

DEF_CMD (ADD , 5, 0,
    {
    Elem_t val = 0;
    DO_PUSH(DO_POP + DO_POP)
    })

DEF_CMD (MUL , 6, 0,
    {
    Elem_t val = 0;
    DO_PUSH(DO_POP * DO_POP / accuracy)
    })

DEF_CMD (SQRT, 7, 0,
    {
    Elem_t val = 0;
    DO_PUSH(sqrt(DO_POP * accuracy))
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
    Elem_t val = -3333333;
    printf("\n\033[33mPrint input value: \033[0m");
    scanf(stack_t, &val);

    while (val == -3333333)
    {
        Clean_buf();

        printf("\n\033[31mIncorrect input!!!\033[0m\n");
        printf("\n\033[33mPrint input value: \033[0m");
        scanf(stack_t, &val);
    }

    DO_PUSH(val)
    })

DEF_CMD (POP , 11, 1,
    {
    Elem_t val = 0;

    *(spu -> args + arg_type) = DO_POP / accuracy;
    })

DEF_CMD (HLT, -1, 0,
    {
    printf("\n\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[31mEND\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[0m\n");
    })

DEF_CMD(NOT, 12, 0,
    {
    Elem_t val = 0;

    DO_PUSH(DO_POP * -1)
    })


