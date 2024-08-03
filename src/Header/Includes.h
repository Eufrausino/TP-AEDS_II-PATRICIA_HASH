#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>

// Defines para processamento de arquivos
#define MAX_FILES 100 // Tamanho máximo de número de arquivos para leitura
#define MAX_FILENAME_LEN 30 // Tamanho do nome do arquivo
#define MAX_LINHA 1024 // Tamanho máximo da linha de leitura do arquivo

// Defines para tabela hash
#define M 23   // Tamanho da tabela hash (escolhendo por meio de testes alfa = 2)
#define TAM 50 // Tamanho ingrediente
#define TAMALFABETO 256 