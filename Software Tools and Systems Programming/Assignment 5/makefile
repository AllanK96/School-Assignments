outfile: operation.o operation_functions.o
        gcc -o outfile operation.o operation_functions.o

operation.o: operation.c operation_functions.h
        gcc -c operation.c

operation_functions.o: operation_functions.c operation_functions.h
        gcc -c operation_functions.c



