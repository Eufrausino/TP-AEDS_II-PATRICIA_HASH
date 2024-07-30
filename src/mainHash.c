#include "Header/Includes.h"
#include "Header/TAD_HASH.h" 

#define MAX_FILES 100
#define MAX_FILENAME_LEN 30
#define MAX_INGREDIENTES 6
#define MAX_LINHA 1024

// Estrutura para armazenar o mapeamento de idDoc para nome do arquivo
typedef struct Document {
    int idDoc;
    char filename[MAX_FILENAME_LEN];
} Document;

// Função para converter uma string para minúsculas
void toLowerCase(char *str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

int ContarOcorrencias(const char *ingrediente, const char *filename) {
    char fullPath[MAX_FILENAME_LEN + 20];
    snprintf(fullPath, sizeof(fullPath), "ArquivosEntrada/%s", filename);

    FILE *file = fopen(fullPath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
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

// Função para remover espaços extras e retirar ponto final
char *trim_whitespace(char *str) {
    char *end;

    // Remover espaços à esquerda
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // Todos os caracteres são espaços?
        return str;

    // Remover espaços à direita
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Remover ponto final, se houver
    if (*end == '.') {
        end--;
    }

    // Adicionar terminador nulo
    end[1] = '\0';

    return str;
}

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


int main() {
    TipoHash hash;

    // Inicializa a tabela hash
    InicializaHash(&hash);

    FILE *inputFile;
    char inputFilename[] = "ArquivosEntrada/entrada.txt";
    char filenames[MAX_FILES][MAX_FILENAME_LEN];
    Document documents[MAX_FILES];
    int N;

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        perror("Erro ao abrir o arquivo entrada.txt");
        return EXIT_FAILURE;
    }

    // Ler o número de documentos N do arquivo entrada.txt
    fscanf(inputFile, "%d", &N);
    //printf("%d", N);

    //Salvar nome arquivos na struct documents com seu respectivo id
    for(int  i=0;i<N;i++){
        fscanf(inputFile, "%s", filenames[i]);
        documents[i].idDoc = i + 1;
        strncpy(documents[i].filename, filenames[i], MAX_FILENAME_LEN);
    }
    
    ProcessaArquivo(&hash, documents, N);

    fclose(inputFile); //Fechar entrada.txt

    ImprimeHash(&hash);

    return 0;
}