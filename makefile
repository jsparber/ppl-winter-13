parity: logic_parity.c makefile
	gcc -ansi -Wall -O logic_parity.c -o parity

clean:
	rm -f logic_parity.o

clean-all:
	rm -f logic_parity.o parity
