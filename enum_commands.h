#define DEF_CMD(name, code, ...) CMD_##name = code,

enum Comands
    {
    #include "commands.h"
    CMD_VERSION = 4
    };
#undef DEF_CMD
