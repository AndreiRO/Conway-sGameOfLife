.PHONY = build clean

build: gol.o bitvector.o main.o
	gcc -Wall src/main.o src/gol.o src/bitvector.o -o tema1

gol.o: src/gol.c
	cd src; make gol.o

bitvector.o: src/bitvector.c
	cd src; make bitvector.o

main.o: src/main.c
	cd src; make main.o

clean:
	rm -rfv src/main.o src/gol.o src/bitvector.o tema1
