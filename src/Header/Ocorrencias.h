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
void ImprimeOcorrencias(TipoOcorrencia *Ocorrencias);