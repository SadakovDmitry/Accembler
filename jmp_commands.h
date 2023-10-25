DO_JMP(JB, 14, 1, < )

DO_JMP(JA, 15, 1, > )

DO_JMP(JAE, 16, 1, >= )

DO_JMP(JBE, 17, 1, <= )

DO_JMP(JE, 18, 1, == )

DO_JMP(JNE, 19, 1, != )

/*
DEF_CMD(JM, 20, 1,
    {
        Elem_t val = 0;
        long int ttime = time(NULL);
        struct tm* now_tm = localtime(&ttime);
        input_func = *(spu -> bin_buf + 1);
        if(now_tm -> tm_wday == 1)
        {
            spu -> bin_buf = start_buf + input_func - 2;
        }
    })
*/
