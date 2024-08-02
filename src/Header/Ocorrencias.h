#ifndef Ocorrencias_H
#define Ocorrencias_H
#include "Includes.h"

typedef struct TipoOcorrencia { //Lista encadeada de ocorrencias
  int idDoc;
  int count;
  struct TipoOcorrencia *Prox;
} TipoOcorrencia;

typedef struct{
  TipoOcorrencia *Primeiro, *Ultimo;
} TipoListaOcorrencias;

void InsereOcorrencia(TipoListaOcorrencias *Ocorrencias, int idDoc, int cont);
int ContarOcorrencias(const char *ingrediente, const char *filename);
<<<<<<< HEAD
void ImprimeOcorrencias(TipoOcorrencia *Ocorrencias);

#endif
=======
void ImprimeOcorrencias(TipoOcorrencia *Ocorrencias);
>>>>>>> branch 'main' of https://github.com/Eufrausino/TP-AEDS_II-PATRICIA_HASH.git
