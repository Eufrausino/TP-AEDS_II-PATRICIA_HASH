#include "../Header/TAD_HASH.h"

// Gera valores aleatórios entre 1 e 10.000
void GeraPesos(TipoPesos p) {
    int i, j;

    // Inicializa o gerador de números aleatórios com a seed fornecida
    srand(4400);

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAMALFABETO; j++) {
            p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
        }
    }
}

// Função de hash para calcular o índice
TipoIndice HashFunction(TipoChave Chave, TipoPesos p) {
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++) {
        Soma += p[i][(unsigned int)Chave[i]];
    }
    return (Soma % M);
}

// Inicializa a tabela hash
void InicializaHash(TipoHash *Hash) {
    for (int i = 0; i < M; i++) {
        Hash->Tabela[i].Primeiro = NULL;
        Hash->Tabela[i].Ultimo = NULL;
    }
    GeraPesos(Hash->Pesos);
}

// Insere um item na tabela hash
void InsereNaHash(TipoHash *Hash, TipoChave Chave, int idDoc, int cont) {
    TipoIndice i = HashFunction(Chave, Hash->Pesos);
    //printf("Para ingrediente %s do arquivo %d o indice: %d\n", Chave, idDoc, i);
    TipoCelula *Celula = Hash->Tabela[i].Primeiro;
    
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
        return;
    }

    // Procura a chave na lista
    while (Celula != NULL) {
        if (strncmp(Chave, Celula->Chave, sizeof(TipoChave)) == 0) {
            InsereOcorrencia(Celula->Ocorrencias, idDoc, cont);
            return;
        }
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
}

// Pesquisa uma chave na tabela hash
TipoCelula* PesquisaNaHash(TipoHash *Hash, TipoChave Chave) {
    TipoIndice i = HashFunction(Chave, Hash->Pesos);
    TipoCelula *Celula = Hash->Tabela[i].Primeiro;

    while (Celula != NULL) {
        if (strncmp(Chave, Celula->Chave, sizeof(TipoChave)) == 0) {
            return Celula;
        }
        Celula = Celula->Prox;
    }
    return NULL;
}



// Imprime a tabela hash
void ImprimeHash(TipoHash *Hash) {
    int i;
    for (i = 0; i < M; i++) {
        printf("%d: ", i);
        TipoCelula *Celula = Hash->Tabela[i].Primeiro;
        while (Celula != NULL) {
            printf("%s ",Celula->Chave);
            ImprimeOcorrencias(Celula->Ocorrencias->Primeiro);
            Celula = Celula->Prox;
        }
        putchar('\n');
    }
}

// Função auxiliar para ler uma palavra da entrada padrão
void LerPalavra(char *p, int Tam) {
    char c;
    int i, j;
    fflush(stdin);
    j = 0;
    while (((c = getchar()) != '\n') && j < Tam - 1) {
        p[j++] = c;
    }
    p[j] = '\0';
    while (c != '\n') {
        c = getchar();
    }

    // Desconsiderar espaços ao final da cadeia
    for (i = j - 1; (i >= 0 && p[i] == ' '); i--) {
        p[i] = '\0';
    }
}
