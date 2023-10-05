struct About_text{
    int rows;
    int text_size;
    char* id_buf;
    int first_or_second_file;
};

struct About_str{
    char* str;
    int len;
};

enum Comands
{
    ZERO = 0,
    HLT  = -1,
    PUSH = 1,
    SUB  = 2,
    DIV  = 3,
    OUT  = 4,
    ADD  = 5,
    MUL  = 6,
    SQRT = 7,
    SIN  = 8,
    COS  = 9,
    IN   = 10
};



int Size_of_text(int* Num_rows, FILE* file);
struct About_str* Input_text (int Num_rows, char* buffer, FILE* file);
void Make_file(struct About_text* ab_text, struct About_str* ab_str);
struct About_str* Work_with_input_file(struct About_text* ab_text, char* buffer, int* Num_rows, FILE* file);
void Clean_buf();
void fill_struct( struct About_text* ab_text, int* Num_rows, int size_of_text, char* buffer);
enum Comands Convert_to_numbers(struct About_str* ab_str, char * now_comand, int i);
void Convert_to_comands(char* str, FILE* output_file);
void Convert_to_cheak_file(struct About_text* ab_text, struct About_str* ab_str);
