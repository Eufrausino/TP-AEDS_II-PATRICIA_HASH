#include "Includes.h"
#include "TAD_HASH.h"

// Estrutura para armazenar o mapeamento de idDoc para nome do arquivo
typedef struct Document {
    int idDoc;
    char filename[MAX_FILENAME_LEN];
} Document;

void ProcessaArquivo(TipoHash *Hash, Document *documents, int numDocuments);
int ContarIngredientes(int idDoc);