#include "Header/Includes.h"
#include "Header/Relevancia.h"
#include "Header/FormataTexto.h"

int main() 
{
    TipoHash hash;
    TipoArvore patricia = NULL;
    InicializaHash(&hash);

    char opcaoMenu;
    char opcao;
    int terminaPrograma = 0;
    //int contadorComparacoes = 0;
    //Optamos por um while para que o usuário não precise ficar executando o programa múltiplas vezes
    while (!terminaPrograma) {
        printf("Selecione uma das seguintes opções:\n");
        printf("a) receber o arquivo de entrada com os textos a serem indexados;\n");
        //src/ArquivosEntrada/entrada.txt
        printf("e) Encerrar programa\n");
        scanf(" %c", &opcaoMenu);
        opcao = tolower(opcaoMenu);

        switch (opcao) {
            case 'a': {
                //Leitura e manipulação dos dados do arquivo de entrada
                FILE *inputFile;
                char arquivoEntrada[500];
                printf("Entre com o caminho relativo do arquivo de entrada:\n");
                scanf("%s", arquivoEntrada);
                char filenames[MAX_FILES][MAX_FILENAME_LEN];
                Document documents[MAX_FILES];
                int N;

                inputFile = fopen(arquivoEntrada, "r");
                if (inputFile == NULL) {
                    perror("Erro ao abrir o arquivo entrada.txt");
                    return EXIT_FAILURE;
                }

                // Ler o número de documentos N do arquivo entrada.txt
                fscanf(inputFile, "%d", &N);

                // Salvar nome dos arquivos na struct documents com seu respectivo id
                for (int i = 0; i < N; i++) {
                    fscanf(inputFile, "%s", filenames[i]);
                    documents[i].idDoc = i + 1;
                    strncpy(documents[i].filename, filenames[i], MAX_FILENAME_LEN);
                }

                fclose(inputFile);
                
                //Como só é possível realizar as operações b,c, d após A
                //um "submenu" iterativo foi feito
                int lacoSwitchInterno = 1;
                while (lacoSwitchInterno) {
                    printf("\nSelecione uma das seguintes opções:\n");
                    printf("b) construir os índices invertidos, a partir dos textos de entrada, usando os TADs PATRICIA e HASH;\n");
                    printf("e) Encerrar programa\n");
                    scanf(" %c", &opcaoMenu);
                    opcao = tolower(opcaoMenu);

                    switch (opcao) {
                        case 'b': {
                            //Compõe os índices invertidos, exibe a quantidade de comparações feitas
                            //em cada estrutura e qual chave foi inserida naquele estado.
                            ProcessaArquivo(&hash, &patricia, documents, N);

                            int lacoSwitchInterno2 = 1;
                            while (lacoSwitchInterno2) {
                                printf("\nSelecione uma das seguintes opções:\n");
                                printf("c) imprimir os índices invertidos, contendo as palavras em ordem alfabética, uma por linha, com suas respectivas listas\n   de ocorrências;\n");
                                printf("d) realizar buscas por um ou mais termo(s) de busca, nos índices construídos, individualmente, apresentando os arquivos\n   ordenados por relevância, também individualmente para cada TAD.\n");
                                printf("e) Encerrar programa\n");
                                scanf(" %c", &opcaoMenu);
                                opcao = tolower(opcaoMenu);

                                switch (opcao) {
                                    case 'c':
                                        //Imprime os índices invertidos
                                        printf("\n-------------------HASH----------------------------------\n");
                                        ImprimeIndiceInvertidoHash(&hash);
                                        printf("\n---------------------------------------------------------\n");
                                        printf("\n--------------------PATRICIA-----------------------------\n");
                                        ImprimeArvore(patricia);
                                        printf("\n---------------------------------------------------------\n");
                                        break;
                                    case 'd': {
                                        //Realiza a busca por relevância
                                        char inputIngredients[MAX_LINHA];
                                        //Por exemplo: "bezoar;castor oil"
                                        printf("Entre com um ou mais ingredientes separados por ';'\n");
                                        getchar(); // Consome \n do scanf
                                        LerPalavra(inputIngredients, MAX_LINHA); //Funciona como scanf p/ string
                                        //printf("%s\n", inputIngredients);
                                        printf("\n-------------------HASH----------------------------------\n");
                                        BuscaRelevanciaHash(&hash, inputIngredients);
                                        printf("\n---------------------------------------------------------\n");
                                        printf("\n--------------------PATRICIA-----------------------------\n");
                                        BuscaRelevanciaPatricia(patricia, inputIngredients);
                                        printf("\n---------------------------------------------------------\n");
                                    }
                                    case 'e':
                                        terminaPrograma = 1;
                                        lacoSwitchInterno = 0;
                                        lacoSwitchInterno2 = 0;
                                        break;
                                    default:
                                        break;
                                }
                            }
                            break;
                        }
                        case 'e':
                            terminaPrograma = 1;
                            lacoSwitchInterno = 0;
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            case 'e':
                terminaPrograma = 1;
                break;
            default:
                break;
        }
    }
    return 0;
}