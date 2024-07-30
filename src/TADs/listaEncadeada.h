#ifndef LISTAENDADEADA_H
#define LISTAENDADEADA_H

#define MAX 10

typedef int TipoChave;

typedef struct {
  int Chave;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista);
int Vazia(TipoLista Lista);
void InsereLista(TipoItem x, TipoLista *Lista);
void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item);
void Imprime(TipoLista Lista);

#endif