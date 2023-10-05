#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Read_file.h"
#include "stack.h"


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
Elem_t pop (struct Stack* stk, struct Canary* canary);

Elem_t Choose_comand(struct Stack* stk, struct Canary* canary, char* str);
void Do_comands (struct About_text* ab_text, struct About_str* ab_str, struct Stack* stk, struct Canary* canary);




Elem_t hlt ()
{
    printf("\n\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[31mEND\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[32m-\033[34m-\033[36m-\033[35m-\033[31m-\033[33m-\033[0m\n");
    return HLT;
}

Elem_t push (struct Stack* stk, struct Canary* canary, char* str)
{
    Elem_t val = (Elem_t) atoi(str + 1);

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
        Clean_buf()

        printf("\n\033[31mIncorrect input!!!\033[0m\n");
        printf("\n\033[33mPrint input value:\033[0m");
        scanf(stack_t, &val);
    }

    Stack_Push(stk, val, canary);

    return val;
}

Elem_t pop (struct Stack* stk, struct Canary* canary)
{
    Elem_t Ret_val = 0;

    Stack_Pop(stk, &Ret_val, canary);


    return Ret_val;
}



Elem_t Choose_comand(struct Stack* stk, struct Canary* canary, char* str)
{
    int func_num = 0;
    int input_func = 0;

    if (sscanf(str, "%d %d", &func_num, &input_func) == 2)
    {
        push(stk, canary, str);
    }
    else
    {
        switch (func_num)
        {
        case HLT:
            hlt ();
            return HLT;
            break;
        case SUB:
            sub (stk, canary);
            break;
        case DIV:
            div (stk, canary);
            break;
        case ADD:
            add (stk, canary);
            break;
        case MUL:
            mul (stk, canary);
            break;
        case SQRT:
            sqrt (stk, canary);
            break;
        case COS:
            cosinus (stk, canary);
            break;
        case SIN:
            sinus (stk, canary);
            break;
        case IN:
            in (stk, canary);
            break;
        case OUT:
            out (stk, canary);
            break;
        case PUSH:
            printf("\n\033[31mIncorrect input!!!\033[0m\n");
            return -1;
        default:
            printf("\n\033[31mIncorrect comand!!!\033[0m\n");
            return -1;
            break;
        }
    }
    return ZERO;
}

void Do_comands (struct About_text* ab_text, struct About_str* ab_str, struct Stack* stk, struct Canary* canary)
{
    assert(ab_text != NULL);
    assert(ab_str != NULL);

    for (int i = 0; i < (ab_text ->rows - 4); i++)
    {
        if (Choose_comand(stk, canary, ab_str[i].str) == -1 )
        {
            break;
        }
    }
}


int main()
{
    struct Canary canary = {};
    struct About_text ab_text = {};
    struct ERRORS ERR = {};
    char* buffer = NULL;
    int Num_rows = 0;
    int capacity = 1;
    ab_text.first_or_second_file = 2;


    FILE* file = fopen("Numbered_comands.txt", "r");

    struct About_str* ab_str = Work_with_input_file(&ab_text, buffer, &Num_rows, file);

    struct Stack* stk = Stack_Ctor( capacity, &ERR, &canary);
    Print_data(stk);

    Do_comands (&ab_text, ab_str, stk, &canary);
}
