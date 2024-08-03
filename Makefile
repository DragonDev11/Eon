output: Eon.o
	gcc Eon.o -o output

Eon.o: Eon.c
	gcc -c Eon.c

clean:
	rm *.o output
