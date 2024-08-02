#include "../Header/ProcessaArquivo.h"
#include "../Header/FormataTexto.h"

// Função para obter a segunda linha do arquivo que são os ingredientes e retornar como string
char* ObterLinhaIngredientes(FILE *file) {
    char buffer[MAX_LINHA];
    int line_number = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_number++;
        if (line_number == 2) {
            return strdup(buffer);  // Copia a linha dos ingredientes
        }
    }
    return NULL;  // Retorna NULL se a linha dos ingredientes não for encontrada
}

// Função para processar arquivos
void ProcessaArquivo(TipoHash *Hash, TipoArvore *patricia, Document *documents, int numDocuments) {
    for (int i = 0; i < numDocuments; i++) {
        char fullPath[MAX_FILENAME_LEN + 30];
        snprintf(fullPath, sizeof(fullPath), "ArquivosEntrada/%s", documents[i].filename);
        //printf("%s", fullPath);

        FILE *file = fopen(fullPath, "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            continue;
        }

        char *ingredientes = ObterLinhaIngredientes(file);

        fclose(file);

        char *start = ingredientes;
        char ingrediente[MAX_LINHA];
        while (1) {
            char *end = strstr(start, "; ");
            if (end != NULL) {
                *end = '\0';
            }

            strncpy(ingrediente, start, MAX_LINHA - 1);
            ingrediente[MAX_LINHA - 1] = '\0';

            toLowerCase(ingrediente);
            trim_whitespace(ingrediente);

            //Inserção na estrutura de dados
            for (int i = 0; i < numDocuments; i++) {
                int total_count = ContarOcorrencias(ingrediente, documents[i].filename);
                if (total_count > 0) {
                    InsereNaHash(Hash, ingrediente, documents[i].idDoc, total_count);
                    *(patricia) = InsereNaPatricia(patricia, ingrediente, documents[i].idDoc, total_count);
                }
            }

            if (end == NULL) break;
            start = end + 2;  // Avança além de "; "
        }
    }
}
