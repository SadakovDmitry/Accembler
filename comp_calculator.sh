g++ -c Read_file.cpp -o Read_file.o
g++ -c Assembler.cpp -o assembler.o
g++ -c SPU_func.cpp -o SPU_func.o
g++ -c stack_functions.cpp -o stack_functions.o
g++ -c Assembler_func.cpp -o assembler_func.o
g++ assembler.o Read_file.o SPU_func.o stack_functions.o assembler_func.o -fsanitize=address -o assembler
./assembler

g++ -c stack_functions.cpp -o stack_functions.o
g++ -c SPU_processor.cpp -o SPU_processor.o
g++ -c SPU_func.cpp -o SPU_func.o
g++ Read_file.o SPU_processor.o stack_functions.o SPU_func.o -fsanitize=address -o SPU
./SPU

g++ -c Convert_to_comands.cpp -o convert_to_comands.o
g++ -c Read_file.cpp -o Read_file.o
g++ convert_to_comands.o Read_file.o -o check
./check



