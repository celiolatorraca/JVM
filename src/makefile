.PHONY: all, apple, java

CC = gcc
FLAGS = -Wall -ansi -pedantic -error -lm -g
AFLAGS = -Wall -ansi -pedantic -lm -g
OBJS = classloader.o methods.o jvmerr.o carregador.o mnemonics.o stack.o heap.o instructions.o types.o frame.o


all: main.c $(OBJS)
	$(CC) main.c -o jvm $(OBJS) $(AFLAGS)
	
apple: main.c $(OBJS)
	$(CC) main.c -o jvm $(OBJS) $(AFLAGS)

debug: main.c $(OBJS)
	$(CC) main.c -o jvm $(OBJS) $(FLAGS) -DDEBUG
	
debug_apple: main.c $(OBJS)
	$(CC) main.c -o jvm $(OBJS) $(AFLAGS) -DDEBUG

java:
	javac -target 1.2 -source 1.2 javaTeste/*.java
	
clean:
	rm *.o

%.o: %.c %.h
	$(CC) $< -o $@ -c $(AFLAGS)