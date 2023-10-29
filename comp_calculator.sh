g++ -c Read_file.cpp -o Read_file.o
g++ -c Assembler.cpp -o assembler.o
g++ -c SPU_func.cpp -o SPU_func.o
g++ -c stack_functions.cpp -o stack_functions.o
g++ -c Assembler_func.cpp -o assembler_func.o
g++ -c Work_SMFL.cpp -o work_sfml.o
g++ assembler.o Read_file.o SPU_func.o stack_functions.o work_sfml.o assembler_func.o -fsanitize=address -o assembler -lsfml-graphics -lsfml-window -lsfml-system
./assembler

g++ -c stack_functions.cpp -o stack_functions.o
g++ -c SPU_processor.cpp -o SPU_processor.o
g++ -c SPU_func.cpp -o SPU_func.o
g++ -c Work_SMFL.cpp -o work_sfml.o
g++ Read_file.o SPU_processor.o stack_functions.o work_sfml.o SPU_func.o -fsanitize=address -o SPU -lsfml-graphics -lsfml-window -lsfml-system
./SPU

g++ -c Convert_to_comands.cpp -o convert_to_comands.o
g++ -c Read_file.cpp -o Read_file.o
g++ -c Work_SMFL.cpp -o work_sfml.o
g++ convert_to_comands.o Read_file.o work_sfml.o -o check -lsfml-graphics -lsfml-window -lsfml-system
./check



