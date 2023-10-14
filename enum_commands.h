/*
enum Comands
{
    CMD_ZERO = 0,
    CMD_HLT  = -1,
    CMD_PUSH = 1,
    CMD_SUB  = 2,
    CMD_DIV  = 3,
    CMD_OUT  = 4,
    CMD_ADD  = 5,
    CMD_MUL  = 6,
    CMD_SQRT = 7,
    CMD_SIN  = 8,
    CMD_COS  = 9,
    CMD_IN   = 10,
    CMD_POP  = 11
};
*/
#define DEF_CMD(name, code, ...) CMD_##name = code,

enum Comands
    {
    #include "commands.h"
    CMD_VERSION = 1
    };
#undef DEF_CMD
