#include "../Header/TAD_HASH.h"

//Funções para Algoritmo QuickSort obtido livro cormen e modificado para tipoCelula/////
int CompararChaves(TipoCelula *a, TipoCelula *b) {
    return strncmp(a->Chave, b->Chave, TAM);
}

int partition(TipoCelula *arr, int left, int right) {
    TipoCelula pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (CompararChaves(&arr[j], &pivot) < 0) {
            i++;
            TipoCelula temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    TipoCelula temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    return i + 1;
}

void QuickSort(TipoCelula *arr, int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        QuickSort(arr, left, pi - 1);
        QuickSort(arr, pi + 1, right);
    }
}
/////////////////////////////////////////////////////////////////////////////////

// Gera valores aleatórios entre 1 e 10.000 (Ziviani)
void GeraPesos(TipoPesos p) {
    int i, j;
    
    //Parte Ziviani
    /*
    struct timeval semente;
    gettimeofday(&semente, NULL); 
    srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
    */ 

    // Inicializa o gerador de números aleatórios com a seed fornecida (meu número de matrícula)
    srand(4400);

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAMALFABETO; j++) {
            p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
        }
    }
}

// Função de hash para calcular o índice (Ziviani)
TipoIndice HashFunction(TipoChave Chave, TipoPesos p) {
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++) {
        Soma += p[i][(unsigned int)Chave[i]];
    }
    return (Soma % M);
}

// Função que inicializa a tabela hash definindo os ponteiros para NULL
void InicializaHash(TipoHash *Hash) {
    for (int i = 0; i < M; i++) {
        Hash->Tabela[i].Primeiro = NULL;
        Hash->Tabela[i].Ultimo = NULL;
    }
    GeraPesos(Hash->Pesos);
}

// FUnção que insere um item na tabela hash
void InsereNaHash(TipoHash *Hash, TipoChave Chave, int idDoc, int cont) {
    TipoIndice i = HashFunction(Chave, Hash->Pesos);
    //printf("Para ingrediente %s do arquivo %d o indice: %d\n", Chave, idDoc, i);
    TipoCelula *Celula = Hash->Tabela[i].Primeiro;
    int comparacoes = 0;

    // Verifica se a lista está vazia
    if (Hash->Tabela[i].Primeiro == NULL) {
        Celula = (TipoCelula *)malloc(sizeof(TipoCelula));
        strncpy(Celula->Chave, Chave, sizeof(TipoChave));
        Celula->Ocorrencias = (TipoListaOcorrencias *)malloc(sizeof(TipoListaOcorrencias));
        Celula->Ocorrencias->Primeiro = NULL;
        Celula->Ocorrencias->Ultimo = NULL;
        Celula->Prox = NULL;

        Hash->Tabela[i].Primeiro = Celula;
        Hash->Tabela[i].Ultimo = Celula;
        
        InsereOcorrencia(Celula->Ocorrencias, idDoc, cont);
        printf("--------------------------------------------HASH---------------------------------------\n");
        printf("Insercao do termo: %s, Comparacoes: %d \n", Chave, comparacoes+1);
        return;
    }

    // Procura a chave na lista
    while (Celula != NULL) {
        if (strncmp(Chave, Celula->Chave, sizeof(TipoChave)) == 0) {
            InsereOcorrencia(Celula->Ocorrencias, idDoc, cont);
            return;
        }
        comparacoes ++;
        Celula = Celula->Prox;
    }

    // Se não encontrou, cria uma nova célula e insere no final da lista
    Celula = (TipoCelula *)malloc(sizeof(TipoCelula));
    strncpy(Celula->Chave, Chave, sizeof(TipoChave));
    Celula->Ocorrencias = (TipoListaOcorrencias*)malloc(sizeof(TipoListaOcorrencias));
    Celula->Ocorrencias->Primeiro = NULL;
    Celula->Ocorrencias->Ultimo = NULL;
    Celula->Prox = NULL;

    Hash->Tabela[i].Ultimo->Prox = Celula;
    Hash->Tabela[i].Ultimo = Celula;

    InsereOcorrencia(Celula->Ocorrencias, idDoc, cont);
    printf("-----------------------------------HASH---------------------------------------\n");
    printf("Insercao do termo: %s, Comparacoes: %d \n", Chave, comparacoes+1);
}

// Função que percorre e imprime cada item da tabela hash
void ImprimeHash(TipoHash *Hash) {
    int i;
    for (i = 0; i < M; i++) {
        printf("%d: ", i);
        TipoCelula *Celula = Hash->Tabela[i].Primeiro;
        while (Celula != NULL) {
            printf("[ ");
            printf("%s ",Celula->Chave);
            ImprimeOcorrencias(Celula->Ocorrencias->Primeiro);
            Celula = Celula->Prox;
            printf("]");
        }
        putchar('\n');
    }
}

// Função que percorre a tabela hash, salva o indice invertido e imprime em ordem alfabética
void ImprimeIndiceInvertidoHash(TipoHash *Hash){
    TipoCelula indiceInvertido[46]; //Vetor contendo 46 ingredientes distintos
    for (int i = 0; i < 46; i++) {
        indiceInvertido[i].Prox = NULL;
    }
    
    // Percorrer cada índice da tabela hash
    int c = 0;
    for (int i = 0; i < M; i++) {
        TipoCelula *Celula = Hash->Tabela[i].Primeiro;
        // Percorrer cada célula na tabela hash
        while (Celula != NULL) {
            strncpy(indiceInvertido[c].Chave, Celula->Chave, TAM - 1); // Copia a chave para indiceInvertido
            indiceInvertido[c].Ocorrencias = Celula->Ocorrencias;
            Celula = Celula->Prox;
            c++;
        }
    }
    
    //Ordenar Indice Invertido em ordem alfabética
    QuickSort(indiceInvertido, 0, 45);

    //Imprime indice invertido
    for (int i = 0; i < 46; i++) {
        printf("%s ", indiceInvertido[i].Chave);
        ImprimeOcorrencias(indiceInvertido[i].Ocorrencias->Primeiro);
        printf("\n");
    }
    
}

