#ifndef PATRICIA_H
#define PATRICIA_H

//Implementações árvore PATRICIA obtidas em: 
//https://www2.dcc.ufmg.br/livros/algoritmos/cap5/codigo/c/5.16a5.21-patricia.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#define D 25 /* depende de TipoChave */

//!!!!ATENÇÃO: OLHAR O TAMANHO DA MAIOR PALAVRA PARA DEFINIR D!!!!!!

typedef unsigned char TipoChave[D] ; /* a definir, dependendo da aplicacao */
typedef int TipoIndexAmp;
typedef unsigned char TipoDib;

typedef enum{
    Interno,
    Externo
} TipoNo;

typedef struct TipoPatNo *TipoArvore;

typedef struct TipoPatNo{
    TipoNo nt;
    union{
        struct{
            TipoIndexAmp Index;
            char letra;
            TipoArvore Esq, Dir;
        } NInterno;
        TipoChave Chave;
    } NO;
} TipoPatNo;

TipoDib Bit(TipoIndexAmp i, TipoChave k);
short EExterno(TipoArvore p);
TipoArvore CriaNoInt(int i, TipoArvore *Esq,  TipoArvore *Dir, char letraDiferente);
TipoArvore CriaNoExt(TipoChave k);
void Pesquisa(TipoChave k, TipoArvore t);
TipoArvore InsereEntre(TipoChave k, TipoArvore *t, int i, char letraDiferente);
TipoArvore Insere(TipoChave k, TipoArvore *t);
void ImprimeArvore(TipoArvore t);

#endif