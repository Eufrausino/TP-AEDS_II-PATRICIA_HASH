#ifndef PROCESSA_ARQUIVOS_H
#define PROCESSA_ARQUIVOS_H
#include "Includes.h"
#include "TAD_HASH.h"
#include "patricia.h"



// Estrutura para armazenar o mapeamento de idDoc para nome do arquivo
typedef struct Document {
    int idDoc;
    char filename[MAX_FILENAME_LEN];
} Document;

void ProcessaArquivo(TipoHash *Hash, TipoArvore *patricia, Document *documents, int numDocuments);

#endif