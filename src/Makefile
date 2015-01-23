.PHONY = build clean
DEBUG = 0

build: bitvector.o gol.o main.o
	gcc -Wall $^ -o ../gol

main.o: main.c
	gcc -Wall -c $^ -o main.o

bitvector.o: bitvector.c bitvector.h
	gcc -Wall  -c $< -o $@

gol.o: gol.c gol.h
	gcc -Wall -D DEBUG=$(DEBUG) -c $< -o $@

clean:
	rm *.o
