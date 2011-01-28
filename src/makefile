.PHONY: all, apple, java

all:
	gcc -Wall -ansi -pedantic -error -lm classloader.c methods.c jvmerr.c carregador.c main.c mnemonics.c stack.c instructions.c types.c frame.c -o jvm -g
	
apple:
	gcc -Wall -ansi -pedantic -lm classloader.c methods.c jvmerr.c carregador.c main.c mnemonics.c stack.c instructions.c types.c frame.c -o jvm -g
	
java:
	cd .. && make java