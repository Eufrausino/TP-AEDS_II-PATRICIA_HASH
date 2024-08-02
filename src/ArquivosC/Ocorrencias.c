#include "../Header/Ocorrencias.h"
#include "../Header/FormataTexto.h"

// Insere uma nova ocorrência na lista encadeada de ocorrências
void InsereOcorrencia(TipoListaOcorrencias *Ocorrencias, int idDoc, int cont) {

    // Inserir primeira ocorrencia se estiver vazio
    if(Ocorrencias->Primeiro == NULL){
        TipoOcorrencia *novaOcorrencia = (TipoOcorrencia *)malloc(sizeof(TipoOcorrencia));
        novaOcorrencia->idDoc = idDoc;
        novaOcorrencia->count = cont;
        novaOcorrencia->Prox = NULL;
        
        Ocorrencias->Primeiro = novaOcorrencia;
        Ocorrencias->Ultimo = novaOcorrencia;
        return;
    }

    // Verifica se a ocorrencia já existe para evitar duplicatas 
    TipoOcorrencia *occ = Ocorrencias->Primeiro;
    while (occ != NULL) {
        if (occ->idDoc == idDoc) {
            return;
        }
        occ = occ->Prox;
    }

    // Insere nova ocorrência ao final
    TipoOcorrencia *novaOcorrencia = (TipoOcorrencia *)malloc(sizeof(TipoOcorrencia));
    novaOcorrencia->idDoc = idDoc;
    novaOcorrencia->count = cont;
    novaOcorrencia->Prox = NULL;

    Ocorrencias->Ultimo->Prox = novaOcorrencia;
    Ocorrencias->Ultimo = novaOcorrencia;
}

int ContarOcorrencias(const char *ingrediente, const char *filename) {
    char fullPath[MAX_FILENAME_LEN + 20];
    snprintf(fullPath, sizeof(fullPath), "ArquivosEntrada/%s", filename);

    FILE *file = fopen(fullPath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        printf("bleble\n");
        return 0;
    }

    char linha[MAX_LINHA];
    int count = 0;

    // Ignorar a primeira linha
    fgets(linha, sizeof(linha), file);

    // Ler cada linha do arquivo
    while (fgets(linha, sizeof(linha), file) != NULL) {
        char *start = linha;
        char *end = NULL;

        while ((end = strstr(start, ";")) != NULL || *start != '\0') {
            if (end != NULL) {
                *end = '\0';
            }

            // Converter para minúsculas
            toLowerCase(start);
            

            // Remover espaços em branco no início e no final
            while (*start == ' ') start++;
            char *tempEnd = start + strlen(start) - 1;
            while (tempEnd > start && *tempEnd == ' ') tempEnd--;
            if (*tempEnd == '.') {
                *tempEnd = '\0';
            } else {
                tempEnd[1] = '\0';
            }

            // Comparar a frase inteira com o ingrediente
            if (strlen(ingrediente) > 4) {  // Verificar se a palavra tem mais de 4 caracteres
                char *current_position = start;
                while ((current_position = strstr(current_position, ingrediente)) != NULL) {
                    size_t len = strlen(ingrediente);

                    // Certificar-se de que a ocorrência é uma palavra completa
                    if ((current_position == start || isspace(*(current_position - 1))) &&
                        (isspace(*(current_position + len)) || *(current_position + len) == '\0' || ispunct(*(current_position + len)))) {
                        count++;
                    }

                    current_position += len;
                }
            }

            if (end != NULL) {
                start = end + 1;
            } else {
                break;
            }
        }
    }

    fclose(file);
    return count;
}


// Imprime a lista de ocorrências (função encapsulada para utilizar na impressão da tabela hash)
void ImprimeOcorrencias(TipoOcorrencia *Ocorrencias) {
    while (Ocorrencias != NULL) {
        printf("[Doc ID: %d, Count: %d] ", Ocorrencias->idDoc, Ocorrencias->count);
        Ocorrencias = Ocorrencias->Prox;
    }
}
