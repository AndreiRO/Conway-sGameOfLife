.PHONY = clean


test_bitvector: test_bitvector.o bitvector.o
	gcc test_bitvector.o ../src/bitvector.o -o test_bitvector

bitvector.o:
	cd ../src; make bitvector.o;

test_bitvector.o: test_bitvector.c
	gcc -Wall -c test_bitvector.c -o test_bitvector.o

test_gol: gol.o test_gol.c bitvector.o
	gcc -Wall -c test_gol.c -o test_gol.o
	gcc -Wall ../src/gol.o test_gol.o ../src/bitvector.o -o test_gol

gol.o:
	cd ../src; make gol.o;

clean:
	rm -rfv test.o test_gol.o ../src/gol.o ../src/bitvector.o test_gol test_bitvector
