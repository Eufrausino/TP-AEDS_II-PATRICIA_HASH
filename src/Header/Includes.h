#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Defines para processamento de arquivos
#define MAX_FILES 100
#define MAX_FILENAME_LEN 30
#define MAX_INGREDIENTES 6
#define MAX_LINHA 1024

// Defines para tabela hash
#define M 29   // Tamanho da tabela hash (29 é o número primo próximo de 27 = 0.6 * 46 ingredientes distintos)
#define TAM 50      
#define TAMALFABETO 256