EXEC = exec
SRCDIR = src
TADSDIR = $(SRCDIR)/TADs
SRC = $(SRCDIR)/main.c $(TADSDIR)/patricia.c $(TADSDIR)/listaEncadeada.c
OBJ = $(SRCDIR)/main.o $(TADSDIR)/patricia.o $(TADSDIR)/listaEncadeada.o
CC = gcc
CFLAGS = -I$(TADSDIR)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

$(SRCDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TADSDIR)/patricia.o: $(TADSDIR)/patricia.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TADSDIR)/listaEncadeada.o: $(TADSDIR)/listaEncadeada.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean