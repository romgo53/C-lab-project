assembler: main.o pre_assembler.o file_handler.o first_pass.o second_pass.o error_handler.o symbols_handler.o data_handler.o entry_handler.o utils.o word_handler.o
	gcc -Wall -ansi -pedantic main.o pre_assembler.o file_handler.o first_pass.o second_pass.o error_handler.o symbols_handler.o data_handler.o entry_handler.o utils.o word_handler.o -o assembler

main.o: main.c
	gcc -c -Wall -ansi -pedantic main.c -o main.o

pre_assembler.o: pre_assembler.c
	gcc -c -Wall -ansi -pedantic pre_assembler.c -o pre_assembler.o

file_handler.o: file_handler.c
	gcc -c -Wall -ansi -pedantic file_handler.c -o file_handler.o

first_pass.o: first_pass.c
	gcc -c -Wall -ansi -pedantic first_pass.c -o first_pass.o

second_pass.o: second_pass.c
	gcc -c -Wall -ansi -pedantic second_pass.c -o second_pass.o

error_handler.o: error_handler.c
	gcc -c -Wall -ansi -pedantic error_handler.c -o error_handler.o

symbols_handler.o: symbols.c
	gcc -c -Wall -ansi -pedantic symbols.c -o symbols_handler.o

data_handler.o: data_handler.c
	gcc -c -Wall -ansi -pedantic data_handler.c -o data_handler.o

entry_handler.o: entry_handler.c
	gcc -c -Wall -ansi -pedantic entry_handler.c -o entry_handler.o


utils.o: utils.c
	gcc -c -Wall -ansi -pedantic utils.c -o utils.o

word_handler.o: word_handler.c
	gcc -c -Wall -ansi -pedantic word_handler.c -o word_handler.o