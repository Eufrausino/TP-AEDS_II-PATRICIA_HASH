#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header/patricia.h"



TipoDib Bit(TipoIndexAmp i, TipoChave k){
 /* Retorna a i-esima letra da chave k a partir da esquerda */
	return k[i];
}

short EExterno(TipoArvore p){
/* Verifica se p é nó externo */
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
    return p;
}

TipoArvore CriaNoExt(TipoChave k, int idDoc, int cont, int *contadorComparacoes){
    TipoArvore p;
    int i;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    strcpy(p->NO.NExterno.Chave, k);
    p->NO.NExterno.ocorrencias.Primeiro = NULL;
    InsereOcorrencia(&(p->NO.NExterno.ocorrencias), idDoc, cont);
    printf("Insercao do termo: %s, Comparacoes: %d \n", p->NO.NExterno.Chave, *(contadorComparacoes));
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

TipoArvore InsereEntre(TipoChave k, TipoArvore *t, int i, char letraDiferente, int idDoc, int cont, int* contadorComparacoes){
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index){
        (*contadorComparacoes)++;
        p = CriaNoExt(k, idDoc, cont, contadorComparacoes);
        
        // se k[i] for >= a letradiferente; t(raiz da arvore) vai pra esquerda e o no atual vao para a direita
        if (Bit(i, k) >= letraDiferente){
            (*contadorComparacoes)++;
            return (CriaNoInt(i, t, &p, letraDiferente));
        }
        else{
            (*contadorComparacoes)++;
            // nó atual vai pra esquerda e t(raiz) vai pra direita
            return (CriaNoInt(i, &p, t, letraDiferente));
        }
    }
    else {
        (*contadorComparacoes)++;
    	if (Bit((*t)->NO.NInterno.Index, k) >= (*t)->NO.NInterno.letra){
            (*contadorComparacoes)++;
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, letraDiferente, idDoc, cont, contadorComparacoes);
        }
        else{
            (*contadorComparacoes)++;
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, letraDiferente, idDoc, cont, contadorComparacoes);
        }
        return (*t);
    }
}

TipoArvore InsereNaPatricia(TipoArvore *t, TipoChave k, int idDoc, int cont, int* contadorComparacoes){
    TipoArvore p;
    int i;
    char letraDiferente;
    //conta o numero de comparações
    (*contadorComparacoes)++;
    //verifica se a árvore é nula
    if (*t == NULL){
        return (CriaNoExt(k, idDoc, cont, contadorComparacoes));
    }
    else{
        p = *t;
        //percorre a arvore até se encontrar um nó externo
        //compara-s o bit de K com o armazenado no nó interno da arvore
        //decide-se a partir disso a direção a ser percorrida
        while (!EExterno(p)){
            (*contadorComparacoes)++;
            if (Bit(p->NO.NInterno.Index, k) >= p->NO.NInterno.letra){
                p = p->NO.NInterno.Dir;
            }
            else
                p = p->NO.NInterno.Esq;
        }
        /* acha o primeiro bit diferente */
        i = 0;
        while ((i <= D) & (Bit((int)i, k) == Bit((int)i, p->NO.NExterno.Chave))){
            i++;
            (*contadorComparacoes)++;
        }
        //guarda a letra  da palavra que diferencia (sempre vai ser a maior letra)
        letraDiferente = k[i] >= p->NO.NExterno.Chave[i] ? k[i] : p->NO.NExterno.Chave[i];
        (*contadorComparacoes)++;
        
        //compara o ingrediente a ser inserido(K) com o ingrediente já presente na arvore(chave)
        //se forem diferentes insere a nova ocorrencia sem inserir novamente o ingrediente
        if (!(strcmp(k, p->NO.NExterno.Chave))){
            (*contadorComparacoes)++;
            InsereOcorrencia(&(p->NO.NExterno.ocorrencias), idDoc, cont);
            return (*t);
        }
        else
            return (InsereEntre(k, t, i, letraDiferente, idDoc, cont, contadorComparacoes));
    }
}

// Função para imprimir a árvore Patricia
void ImprimeArvore(TipoArvore t) {
    if (t != NULL) {
        if (EExterno(t)) {
            printf("%s - ", t->NO.NExterno.Chave);
            ImprimeOcorrencias(t->NO.NExterno.ocorrencias.Primeiro);
            printf("\n");
        } else {
            ImprimeArvore(t->NO.NInterno.Esq);
            ImprimeArvore(t->NO.NInterno.Dir);

        }
    }
}
