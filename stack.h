typedef int Elem_t;
typedef unsigned long long canary_t;


//#define CANARY_ON 1
//#define HASH_ON 1


#define STACK_DUMP(stk, canary) Stack_Dump(stk, canary, (char*)__FILE__, __LINE__, __func__);
#define stack_t "%d"


#ifdef CANARY_ON
    #define size_canary (2 * sizeof ( canary_t ))
#else
    #define size_canary 0
#endif


enum Errors : unsigned int
{
    NO_ERROR                = 0,
    DATA_NULL               = 1 << 0,
    CAPACITY_ZERO           = 1 << 1,
    STK_NULL                = 1 << 2,
    CAPASITY_TOO_SMALL      = 1 << 3,
    DATA_WAS_RUBBISHED      = 1 << 4,
    STK_WAS_RUBBISHED       = 1 << 6,
    LEFT_CANARY_DATA_DIE    = 1 << 7,
    RIGHT_CANARY_DATA_DIE   = 1 << 8,
    LEFT_CANARY_STK_DIE     = 1 << 9,
    RIGHT_CANARY_STK_DIE    = 1 << 10,
    HASH_WAS_CHANGED        = 1 << 11,
    DIE_STK                 = 1 << 12,
    SIZE_SMALLER_THEN_ZERO  = 1 << 13
};




struct Stack
{
    Elem_t* data;
    int size;
    int capacity;
    Elem_t poizon;
    Elem_t hash;
    Elem_t last_hash;
    unsigned int Code_err;
    int die_stk;
};

struct Canary
{
    canary_t* left_canary_data;
    canary_t* right_canary_data;
    canary_t* left_canary_stk;
    canary_t* right_canary_stk;
};

struct ERRORS
{
    Errors err;
};



void Put_canary(struct Stack* stk, struct Canary* canary);
void Canareyca_Protection(struct Stack* stk, struct Canary* canary);
int Hash_Protection(struct Stack* stk);
int Calculate_Hash(struct Stack* stk);
struct Stack* Stack_Ctor( int capacity, struct ERRORS* ERR, struct Canary* canary);
int Stack_Dtor(struct Stack* stk, struct Canary* canary);
int Stack_Push(struct Stack* stk, Elem_t val, struct Canary* canary);
int Stack_Pop(struct Stack* stk, Elem_t* Ret_val, struct Canary* canary);
int Stack_Dump(struct Stack* stk, struct Canary* canary, char* file , int line, const char* func);
int Stack_Realloc(struct Stack* stk, struct Canary* canary);
int Stack_Realloc_Press(struct Stack* stk, struct Canary* canary);
unsigned int StackErr(struct Stack* stk, struct Canary* canary);
void Print_data(struct Stack* stk);
void Cycle_push(struct Stack* stk, Elem_t* val, struct Canary* canary);
void Cycle_pop(struct Stack* stk, Elem_t* Ret_val, struct Canary* canary);
void Strinput(char* input_str);
int Cmp_two_str(char* input_str, char* answer);
void Clean_buf();
