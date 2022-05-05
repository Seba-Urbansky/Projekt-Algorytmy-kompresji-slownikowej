CC=gcc
CFLAGS=-I.
DEPS = lz78.h lzw.h lzw_slownik.h lzw_tablica.h
OBJ = main.o lz78.o lzw.o lzw_slownik.o lzw_tablica.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)