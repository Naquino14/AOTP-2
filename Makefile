CFLAGS = -ggdb -Wall -Wextra -pedantic -std=c99 -Wno-unknown-pragmas

program: lib/ACH-2.o AOTP-2.o program.o
	gcc -o program $(CFLAGS) lib/ACH-2.o AOTP-2.o program.o -lm

program.o: program.c AOTP-2.c lib/ACH-2.c
	gcc -c program.c $(CFLAGS)

AOTP-2.o: AOTP-2.c lib/ACH-2.o
	gcc -c AOTP-2.c $(CFLAGS)

lib/ACH-2.o: lib/ACH-2.c
	cd lib/ && gcc -c ACH-2.c $(CFLAGS)

clean:
	rm -r *.o program lib/*.o