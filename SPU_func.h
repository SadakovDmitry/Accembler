#define SPU_DUMP(spu) SPU_Dump(spu, (char*)__FILE__, __LINE__, __func__);
#define NUM_ARGS 4

const int SIZE_OF_RAM = 20000;

void Do_comands (struct About_text* ab_text, struct Stack* stk, struct Stack* stk_calls, struct Canary* canary, struct SPU* spu);

unsigned int SPU_Verify(struct SPU* spu);
void SPU_Dump(struct SPU* spu, char* file , int line, const char* func);
void SPU_Dtor(struct Stack* stk, struct Canary* canary, struct SPU* spu);
void SPU_Ctor(struct Stack* stk, struct Canary* canary, struct SPU* spu);
