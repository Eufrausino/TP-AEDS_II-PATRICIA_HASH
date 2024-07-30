#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"

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

TipoArvore CriaNoExt(TipoChave k){
    TipoArvore p;
    int i;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    for(i = strlen(k); i < D; i++){ //preenche as posições da palavra com \0
    	k[i] = '\0';
    }
    strcpy(p->NO.Chave, k);
    //printf("XXXXXXXXXXXXXXXXXX: %d", k[24]);
    return p;
}

void Pesquisa(TipoChave k, TipoArvore t){
    if (EExterno(t)){
        if (strcmp(k,t->NO.Chave) == 0)
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

TipoArvore InsereEntre(TipoChave k, TipoArvore *t, int i, char letraDiferente){
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index){
         /* cria um novo no externo */
        p = CriaNoExt(k);
        if (Bit(i, k) >= letraDiferente)
            return (CriaNoInt(i, t, &p, letraDiferente));
        else
            return (CriaNoInt(i, &p, t, letraDiferente));
    }
    else {
    	if (Bit((*t)->NO.NInterno.Index, k) >= (*t)->NO.NInterno.letra) // esse era o probelma!!!!! Compara k na posicao do indice e a letra do no interno
        //if (letraDiferente >= (*t)->NO.NInterno.letra) //TODO probema aqui!!!!!
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, letraDiferente);
        else
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i, letraDiferente);
        return (*t);
    }
}

TipoArvore Insere(TipoChave k, TipoArvore *t){
    TipoArvore p;
    int i;
    char letraDiferente;
    if (*t == NULL)
        return (CriaNoExt(k));
    else{
        p = *t;
        while (!EExterno(p)){
            if (Bit(p->NO.NInterno.Index, k) >= p->NO.NInterno.letra)
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
        }
        /* acha o primeiro bit diferente */
        i = 0;
        while ((i <= D) & (Bit((int)i, k) == Bit((int)i, p->NO.Chave)))
            i++;
        letraDiferente = k[i] >= p->NO.Chave[i] ? k[i] : p->NO.Chave[i]; //guarda a letra  da palavra que diferencia (sempre vai ser a maior letra)
        if (i >= D){
            printf("Erro: chave ja esta na arvore\n");
            return (*t);
        }
        else
            return (InsereEntre(k, t, i, letraDiferente));
    }
}
// imprime a patricia em ordem alfabética
void ImprimeArvore(TipoArvore t) {
    if (t == NULL) return;

    if (EExterno(t)) {
        printf("%s\n", t->NO.Chave);
    }
    else {
        ImprimeArvore(t->NO.NInterno.Esq);
        ImprimeArvore(t->NO.NInterno.Dir);
    }
}