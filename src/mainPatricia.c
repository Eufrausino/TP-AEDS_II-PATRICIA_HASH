#include "Header/Includes.h"
#include "Header/ProcessaArquivo.h" 
#include "Header/patricia.h"



int main(){

	TipoHash hash;

    // Inicializa a tabela hash
    InicializaHash(&hash);

	//inicializa arvore patrícia
	TipoArvore patricia = NULL;


	//Insere cada chave na arvore

FILE *inputFile;
    char inputFilename[] = "ArquivosEntrada/entrada.txt";
    char filenames[MAX_FILES][MAX_FILENAME_LEN];
    Document documents[MAX_FILES];
    int N;

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("blabla\n");
        perror("Erro ao abrir o arquivo entrada.txt");
        return EXIT_FAILURE;
    }

    // Ler o número de documentos N do arquivo entrada.txt
    fscanf(inputFile, "%d", &N);
    //printf("%d", N);
    
    //Salvar nome arquivos na struct documents com seu respectivo id
    for(int i=0; i<N;i++){
        fscanf(inputFile, "%s", filenames[i]);
        documents[i].idDoc = i + 1;
        strncpy(documents[i].filename, filenames[i], MAX_FILENAME_LEN);
    }

    
    ProcessaArquivo(&hash, &patricia, documents, N);

    fclose(inputFile); //Fechar entrada.txt

    //ImprimeHash(&hash);
    ImprimeArvore(patricia);

    return 0;
}
