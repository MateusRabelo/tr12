all: run

run: compile
	./main

compile: main.c
	gcc -o main main.c

clean:
	rm -rf *.o main