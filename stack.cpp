#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"





int main()
{
Elem_t val = 0;
Elem_t Ret_val = 0;
int capacity = 0;
struct ERRORS ERR = {};
struct Canary canary = {};


printf("Print capacity of stack: ");
scanf(stack_t, &capacity);

struct Stack* stk = Stack_Ctor( capacity, &ERR, &canary);
Print_data(stk);

Cycle_push(stk, &val, &canary);
Cycle_pop(stk, &Ret_val, &canary);

Print_data(stk);

Stack_Dtor(stk, &canary);

}

