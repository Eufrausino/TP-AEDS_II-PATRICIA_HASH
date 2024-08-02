#ifndef HASH_h
#define HASH_h
#include "Ocorrencias.h"
#include "Includes.h"

typedef char TipoChave[TAM]; //Tamanho ingrediente
typedef unsigned TipoPesos[TAM][TAMALFABETO];
typedef unsigned int TipoIndice;

typedef struct TipoCelula { //Lista encadeada de ingredientes
  TipoChave Chave;
  struct TipoCelula *Prox;
  TipoListaOcorrencias *Ocorrencias; // Lista de ocorrências
} TipoCelula;

typedef struct{
  TipoCelula *Primeiro, *Ultimo;
} TipoListaIngrediente;

typedef struct TipoHash{ //Tabela hash
  TipoListaIngrediente Tabela[M];  // Vetor de listas encadeadas para tratar colisões
  TipoPesos Pesos;
} TipoHash;


void InicializaHash(TipoHash *Hash);
TipoIndice HashFunction(TipoChave Chave, TipoPesos Pesos);
void GeraPesos(TipoPesos Pesos);
void InsereNaHash(TipoHash *Hash, TipoChave Chave, int idDoc, int cont);
TipoCelula* PesquisaNaHash(TipoHash *Hash, TipoChave Chave);
void ImprimeHash(TipoHash *Hash);

#endif