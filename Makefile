COMPILE = gcc -O3 -pipe -Wall

package: objects
	ar -rc libmstr.a mstr.o
	rm -f mstr.o

objects:
	$(COMPILE) -c mstr.c

test:
	$(COMPILE) mstr.c test.c -o mstr.test

clean:
	rm -f mstr.o
	rm -f libmstr.a