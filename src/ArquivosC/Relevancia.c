#include "../Header/Relevancia.h"

// Função para implementar InsertionSort no vetor vetRel (escolhido por simplicidade e vetor de tamanho pequeno)
void insertionSort(TipoRelevancia *vetRel, int size) {
    for (int i = 1; i < size; i++) {
        TipoRelevancia temp = vetRel[i];
        int j = i - 1;
        
        while (j >= 0 && vetRel[j].rel > temp.rel) {
            vetRel[j + 1] = vetRel[j];
            j--;
        }
        vetRel[j + 1] = temp;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para percorrer a tabela hash a partir dos ingredientes informados
void BuscaRelevanciaHash(TipoHash *Hash, char *inputIngredients) { 
    // Fazer uma cópia da string inputIngredients para ser modificada (baseada no processar arquivo)
    char inputCopia[MAX_LINHA];
    strncpy(inputCopia, inputIngredients, MAX_LINHA - 1);
    inputCopia[MAX_LINHA - 1] = '\0'; //Garante que termina em nulo

    TipoRelevancia vetRel[15] = {0};

    // Percorre cada ingrediente de inputCopia
    char *start = inputCopia;
    char ingrediente[MAX_LINHA];
    while (start != NULL) {
        // Localiza o próximo ';' ou o final da string
        char *end = strstr(start, ";");

        if (end != NULL) {
            *end = '\0';  // Modifica a cópia da string
        }

        // Copia o ingrediente atual para a variável ingrediente
        strncpy(ingrediente, start, MAX_LINHA - 1);
        ingrediente[MAX_LINHA - 1] = '\0';

        // Percorrer a tabela hash para calcular a relevância dos ingredientes inseridos
        int comparacoes = 0;
        TipoIndice i = HashFunction(ingrediente, Hash->Pesos);
        TipoCelula *Celula = Hash->Tabela[i].Primeiro;
        //printf("PRIMEIRA CHAVE ENCOTRADA : %s\n", Celula->Chave);

        while (Celula != NULL) {
            comparacoes ++;
            if (strcmp(ingrediente, Celula->Chave) == 0) { //Celula encontrada
                CalculaRelevancia(Celula->Ocorrencias, vetRel); // Calcula relevancia e armazena no vetor  
                printf("Busca do termo: %s, Comparacoes: %d \n", ingrediente, comparacoes+1);
            }
            Celula = Celula->Prox;
        }

        
        // Avança para o próximo ingrediente após ";"
        start = (end != NULL) ? end + 1 : NULL;
    }

    // Ordenando vetor para imprimir relevância na ordem
    insertionSort(vetRel, 15);

    // Exibindo os textos ordenados
    printf("\n");
    for (int i = 14; i >= 0; i--) {
        if (vetRel[i].rel > 0.0) {
            printf("Texto %d (arquivo%d.txt) = %f\n", vetRel[i].idDoc, vetRel[i].idDoc, vetRel[i].rel);
        }
    }
}

// Função que calcula relevancia a partir das fórmulas propostas no TP
void CalculaRelevancia(TipoListaOcorrencias *Ocorrencias, TipoRelevancia* vetRel) {
    // Calcular número de arquivos que a palavra aparece
    TipoOcorrencia *occ = Ocorrencias->Primeiro;
    int d = 0; // Número de docs que a palavra aparece
    while (occ != NULL) {
        d++;
        occ = occ->Prox;
    }

    double rel = 0.0;
    
    occ = Ocorrencias->Primeiro;
    while (occ != NULL) {
        //printf("Para <%d, %d> ", occ->count, occ->idDoc);
        int f = occ->count; // Numero de ocorrencias dentro do documento
        int N = 15; // Numero de documentos
        double w = (f * log2(15) / d); 
        int n = ContarIngredientes(occ->idDoc); //Numero de ingredientes por arquivo
        //printf("Arquivo %d: w = (%d) * Log2(%d)/ %d", occ->idDoc, f, N, d);
        rel =  w/n;
        //printf("Em vet[%d]: somando %f com %f\n", occ->idDoc-1, vetRel[occ->idDoc-1].rel, rel);
        vetRel[occ->idDoc-1].rel += rel;
        vetRel[occ->idDoc-1].idDoc = occ->idDoc;
        //printf(" rel = %f  para arquivo%d", rel, vetRel[i].idDoc);
        occ = occ->Prox;
    }
}

void PesquisaPorChaveCalculaRelevancia(TipoChave k, TipoArvore t,TipoRelevancia* vetRel){
    if (t == NULL) {
        return;
    }
    if (EExterno(t)){
        if (strcmp(k,t->NO.NExterno.Chave) == 0)
        {
            CalculaRelevancia(&(t->NO.NExterno.ocorrencias),vetRel);
        }
        else
            printf("Elemento nao encontrado\n");
        return;
    }
    if (Bit(t->NO.NInterno.Index, k) < t->NO.NInterno.letra) {
        if (t->NO.NInterno.Esq == NULL) {
            printf("Subárvore esquerda nula\n");
        } else {
            PesquisaPorChaveCalculaRelevancia(k, t->NO.NInterno.Esq, vetRel);
        }
    } else {
        if (t->NO.NInterno.Dir == NULL) {
            printf("Subárvore direita nula\n");
        } else {
            PesquisaPorChaveCalculaRelevancia(k, t->NO.NInterno.Dir, vetRel);
        }
    }
}

void BuscaRelevanciaPatricia(TipoArvore pat, char* inputIngredients)
{
    // Fazer uma cópia da string inputIngredients para ser modificada (baseada no processar arquivo)
    char inputCopia[MAX_LINHA];
    strncpy(inputCopia, inputIngredients, MAX_LINHA - 1);
    inputCopia[MAX_LINHA - 1] = '\0'; //Garante que termina em nulo

    TipoRelevancia vetRel[15] = {0};

    // Percorre cada ingrediente de inputCopia
    char *start = inputCopia;
    char ingrediente[MAX_LINHA];
    while (start != NULL) {
        // Localiza o próximo ';' ou o final da string
        char *end = strstr(start, ";");
        if (end != NULL) {
            *end = '\0';  // Modifica a cópia da string
        }
        // Copia o ingrediente atual para a variável ingrediente
        strncpy(ingrediente, start, MAX_LINHA - 1);
        ingrediente[MAX_LINHA - 1] = '\0';
        //------------------------------------------------------------------------ AQUI
        PesquisaPorChaveCalculaRelevancia(ingrediente,pat,vetRel);
        // Avança para o próximo ingrediente após ";"
        start = (end != NULL) ? end + 1 : NULL;
    }
    // Ordenando vetor para imprimir relevância na ordem
    insertionSort(vetRel, 15);

    // Exibindo os textos ordenados
    printf("\n");
    for (int i = 14; i >= 0; i--) {
        if (vetRel[i].rel > 0.0) {
            printf("Texto %d (arquivo%d.txt) = %f\n", vetRel[i].idDoc, vetRel[i].idDoc, vetRel[i].rel);
        }
    }
}