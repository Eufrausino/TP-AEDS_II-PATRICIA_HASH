#include "../Header/ProcessaArquivo.h"
#include "../Header/FormataTexto.h"

// Função para processar arquivos
void ProcessaArquivo(TipoHash *Hash, Document *documents, int numDocuments) {
    for (int i = 0; i < numDocuments; i++) {
        char fullPath[MAX_FILENAME_LEN + 30];
        snprintf(fullPath, sizeof(fullPath), "ArquivosEntrada/%s", documents[i].filename);
        //printf("%s", fullPath);

        FILE *file = fopen(fullPath, "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            continue;
        }

        char buffer[MAX_LINHA];
        char *ingredientes = NULL;
        int line_number = 0;

        // Lendo as linhas do arquivo
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            line_number++;
            if (line_number == 2) {
                // Copiando a linha dos ingredientes
                ingredientes = strdup(buffer);
                //Linha ingredientes encontrada
                break;
            }
        }

        fclose(file);

        // Separando os ingredientes
        char *start = ingredientes;
        char *end = strstr(start, "; ");
        while (end != NULL) {
            *end = '\0';

            // Cria uma cópia do ingrediente para modificações
            char ingrediente[MAX_LINHA];
            strncpy(ingrediente, start, MAX_LINHA - 1);
            ingrediente[MAX_LINHA - 1] = '\0';  // Garante que a string está terminada em '\0'

            // Convertendo para minúsculas e removendo espaços extras e ponto final
            toLowerCase(ingrediente);
            trim_whitespace(ingrediente);

            // Contar as ocorrências do ingrediente em todos os arquivos
            for (int i = 0; i < numDocuments; i++) {
                int total_count = ContarOcorrencias(ingrediente, documents[i].filename);
                
                if (total_count > 0) {
                    //printf("'%s' - <%d,%d>\n", ingrediente, documents[i].idDoc, total_count);
                    InsereNaHash(Hash, ingrediente, documents[i].idDoc, total_count);
                }
            }

            // Avançar para o próximo ingrediente
            start = end + 2; // Avançar além de "; "
            end = strstr(start, "; ");
        }

        // Processar o último ingrediente (caso não tenha um delimitador no final)
        if (*start != '\0') {
            char ingrediente[MAX_LINHA];
            strncpy(ingrediente, start, MAX_LINHA - 1);
            ingrediente[MAX_LINHA - 1] = '\0';  // Garantir que a string está terminada em '\0'

            // Convertendo para minúsculas e removendo espaços extras e ponto final
            toLowerCase(ingrediente);
            trim_whitespace(ingrediente);

            // Contar as ocorrências do ingrediente em todos os arquivos
            for (int i = 0; i < numDocuments; i++) {
                int total_count = ContarOcorrencias(ingrediente, documents[i].filename);

                // Imprimindo o resultado
                if (total_count > 0) {
                    //printf("'%s' - <%d,%d>\n", ingrediente, documents[i].idDoc, total_count);
                    InsereNaHash(Hash, ingrediente, documents[i].idDoc, total_count);
                }
            }
        }

        free(ingredientes);
    }
}
