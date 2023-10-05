g++ -c Read_file.cpp -o Read_file.o
g++ -c Assembler.cpp -o assembler.o
g++ assembler.o Read_file.o -fsanitize=address -o assembler
./assembler

g++ -c stack_functions.cpp -o stack_functions.o
g++ -c SPU_processor.cpp -o SPU_processor.o
g++ Read_file.o SPU_processor.o stack_functions.o -o SPU
./SPU


g++ Convert_to_comands.cpp Read_file.cpp -fsanitize=address -o decoder
./decoder
