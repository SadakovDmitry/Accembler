#define SPU_DUMP(spu) SPU_Dump(spu, (char*)__FILE__, __LINE__, __func__);
#define NUM_ARGS 4

/*
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
*/



void Do_comands (struct About_text* ab_text, struct Stack* stk, struct Canary* canary, struct SPU* spu);

unsigned int SPU_Verify(struct SPU* spu);
void SPU_Dump(struct SPU* spu, char* file , int line, const char* func);
void SPU_Dtor(struct Stack* stk, struct Canary* canary, struct SPU* spu);
void SPU_Ctor(struct Stack* stk, struct Canary* canary, struct SPU* spu);
