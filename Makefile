CC=gcc
CFLAGS=-I.
DEPS = lz78.h lzw.h
OBJ = main.o lz78.o lzw.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)