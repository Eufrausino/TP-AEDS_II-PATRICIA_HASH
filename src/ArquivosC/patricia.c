#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header/patricia.h"



TipoDib Bit(TipoIndexAmp i, TipoChave k){
 /* Retorna a i-esima letra da chave k a partir da esquerda */
	return k[i];
}

short EExterno(TipoArvore p){
/* Verifica se p^ e nodo externo */
    return (p->nt == Externo);
}

TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir, char letraDiferente){
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = i;
    p->NO.NInterno.letra = letraDiferente;
    //printf("XXXXX: %c\n", letraDiferente);
    return p;
}

TipoArvore CriaNoExt(TipoChave k, int idDoc, int cont){
    TipoArvore p;
    //int i;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    strcpy(p->NO.NExterno.Chave, k);
//    for(i = strlen(k); i < D; i++){ //preenche as posições da palavra com \0
//    	p->NO.NExterno.Chave[i] = '\0';
//    }
    //printf("XXXXXXXXXXXXXXXXXX: %d", k[24]);
    p->NO.NExterno.ocorrencias.Primeiro = NULL;
    InsereOcorrencia(&(p->NO.NExterno.ocorrencias), idDoc, cont);
    return p;
}

void Pesquisa(TipoChave k, TipoArvore t){
    if (EExterno(t)){
        if (strcmp(k,t->NO.NExterno.Chave) == 0)
            printf("Elemento encontrado\n");
        else
            printf("Elemento nao encontrado\n");
        return;
    }
    if (Bit(t->NO.NInterno.Index, k) < t->NO.NInterno.letra)
        Pesquisa(k, t->NO.NInterno.Esq);
    else
        Pesquisa(k, t->NO.NInterno.Dir);
}

TipoArvore InsereEntre(TipoChave k, TipoArvore *t, int i, char letraDiferente, int idDoc, int cont){
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index){
         /* cria um novo no externo */
        p = CriaNoExt(k, idDoc, cont);
        if (Bit(i, k) >= letraDiferente)
            return (CriaNoInt(i, t, &p, letraDiferente));
        else
            return (CriaNoInt(i, &p, t, letraDiferente));
    }
    else {
    	if (Bit((*t)->NO.NInterno.Index, k) >= (*t)->NO.NInterno.letra)
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, letraDiferente, idDoc, cont);
        else
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, letraDiferente, idDoc, cont);
        return (*t);
    }
}

TipoArvore InsereNaPatricia(TipoArvore *t, TipoChave k, int idDoc, int cont){
    TipoArvore p;
    int i;
    char letraDiferente;
    if (*t == NULL)
        return (CriaNoExt(k, idDoc, cont));
    else{
        p = *t;
       // printf("no: %d\n", p->nt);
        while (!EExterno(p)){
        	//printf("haha\n");
            if (Bit(p->NO.NInterno.Index, k) >= p->NO.NInterno.letra){
                p = p->NO.NInterno.Dir;
                //printf("hahaha\n");
            }
            else
                p = p->NO.NInterno.Esq;
        }
        //printf("hehe\n");
        /* acha o primeiro bit diferente */
        i = 0;
        printf("bit1: %c\n", Bit((int)i, k));
        printf("bit2: %c\n", Bit((int)i, p->NO.NExterno.Chave));
        while ((i <= D) & (Bit((int)i, k) == Bit((int)i, p->NO.NExterno.Chave))){
            i++;
        }

        letraDiferente = k[i] >= p->NO.NExterno.Chave[i] ? k[i] : p->NO.NExterno.Chave[i]; //guarda a letra  da palavra que diferencia (sempre vai ser a maior letra)
        printf("i: %d\nD: %d\n", i, D);
        if (i >= strlen(k)){
//            printf("Erro: chave ja esta na arvore\ni = %d\n", i);
            InsereOcorrencia(&(p->NO.NExterno.ocorrencias), idDoc, cont);
            return (*t);
        }
        else
            return (InsereEntre(k, t, i, letraDiferente, idDoc, cont));
    }
}

// imprime a patricia em ordem alfabética
/*void ImprimeArvore(TipoArvore t) {
    if (t == NULL) return;

    if (EExterno(t)) {
        printf("%s\n", t->NO.NExterno.Chave);
        //printf("colocar pra printar ocorrencia! ToDo\n");
    }
    else {
        ImprimeArvore(t->NO.NInterno.Esq);
        ImprimeArvore(t->NO.NInterno.Dir);
    }
}*/



/*void printOcorrencias(TipoListaOcorrencias ocorrencias) {
    TipoOcorrencia *ocorrencia = ocorrencias.Primeiro;
    while (ocorrencia != NULL) {
        printf("<%d,%d>", ocorrencia->idDoc, ocorrencia->count);
        if (ocorrencia->Prox != NULL) {
            printf(", ");
        }
        ocorrencia = ocorrencia->Prox;
    }
}*/

// Função para imprimir a árvore Patricia
void ImprimeArvore(TipoArvore t) {
    if (t != NULL) {
        if (EExterno(t)) {
            printf("'%s' - ", t->NO.NExterno.Chave);
            ImprimeOcorrencias(t->NO.NExterno.ocorrencias.Primeiro);
            printf("\n");
        } else {
            ImprimeArvore(t->NO.NInterno.Esq);
            ImprimeArvore(t->NO.NInterno.Dir);

        }
    }
}
