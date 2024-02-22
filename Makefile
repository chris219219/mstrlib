COMPILE = gcc -O3 -pipe -Wall

package: objects
	ar -rc libmstr.a mstr.o
	rm -f mstr.o

objects:
	$(COMPILE) -c mstr.c

clean:
	rm -f mstr.o
	rm -f libmstr.a