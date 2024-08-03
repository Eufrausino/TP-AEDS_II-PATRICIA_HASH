#include "../Header/ProcessaArquivo.h"
#include "../Header/FormataTexto.h"

// Função que conta retorna o número de ingredientes a partir de cada ";" a partir do idDoc
int ContarIngredientes(int idDoc) {
    char fullPath[MAX_FILENAME_LEN + 30];
    snprintf(fullPath, sizeof(fullPath), "ArquivosEntrada/arquivo%d.txt", idDoc);//Concatenando nome do arquivo
    
    FILE *arquivo = fopen(fullPath, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char linha[MAX_LINHA];
    int contador = 0;

    // Ignorar primeira linha
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return 0; 
    }

    // Lê a segunda linha
    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *p = linha;
        while (*p != '\0') { //Ir até o final da linha
            if (*p == ';') { 
                contador++;
            }
            p++;
        }
    }

    fclose(arquivo);
    //printf("Numero de ingredientes para arquivo%d : %d\n", idDoc,contador+1);
    return contador + 1; // Retorna o número de ingredientes (número de ';' + 1)
}


// Função para obter a segunda linha do arquivo que são os ingredientes e retornar como string
char* ObterLinhaIngredientes(FILE *file) {
    char buffer[MAX_LINHA];
    int line_number = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_number++;
        if (line_number == 2) {
            return strdup(buffer);  // strdup faz uma copia da linha de ingredientes(buffer) que é retornado
        }
    }
    return NULL;  // Retorna NULL se a linha dos ingredientes não for encontrada
}

// Função que processa e percorre cada arquivo
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

        char *start = ingredientes;  //aponta para o início da string de ingredientes.
        char ingrediente[MAX_LINHA]; //armazena ingrediente
        while (1) {
            char *end = strstr(start, "; "); // aponta para primeira ocorrencia de ;
            if (end != NULL) { // transforma ocorrencia de ; em \0
                *end = '\0';
            }

            strncpy(ingrediente, start, MAX_LINHA - 1);
            ingrediente[MAX_LINHA - 1] = '\0';

            // formatando ingrediente
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