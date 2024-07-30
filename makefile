EXEC = exec
HASH_EXEC = mainHash

SRCDIR = src
TADSDIR = $(SRCDIR)/TADs
HASH_SRCDIR = ArquivosC

SRC = $(SRCDIR)/main.c $(TADSDIR)/patricia.c $(TADSDIR)/listaEncadeada.c
HASH_SRC = mainHash.c $(HASH_SRCDIR)/ProcessaArquivo.c $(HASH_SRCDIR)/TAD_HASH.c $(HASH_SRCDIR)/Ocorrencias.c $(HASH_SRCDIR)/FormataTexto.c

OBJ = $(SRC:.c=.o)
HASH_OBJ = $(HASH_SRC:.c=.o)

CC = gcc
CFLAGS = -I$(TADSDIR)

all: $(EXEC) $(HASH_EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(HASH_EXEC): $(HASH_OBJ)
	$(CC) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TADSDIR)/%.o: $(TADSDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(HASH_SRCDIR)/%.o: $(HASH_SRCDIR)/%.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(HASH_OBJ) $(EXEC) $(HASH_EXEC)

cleanall: clean
	rm -f $(OBJ) $(HASH_OBJ) $(EXEC) $(HASH_EXEC)

.PHONY: all clean cleanall
