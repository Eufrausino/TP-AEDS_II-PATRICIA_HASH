#include "Includes.h"
#include "ProcessaArquivo.h"

// Struct para juntar cada arquivo com sua relevancia (útil para o calculo da relevancia)
typedef struct{
    double rel;
    int idDoc;
}TipoRelevancia;

void CalculaRelevancia(TipoListaOcorrencias *Ocorrencias, TipoRelevancia* vetRel);
void BuscaRelevanciaHash(TipoHash *Hash,char *inputIngredients);
void BuscaRelevanciaPatricia(TipoArvore pat, char* inputIngredients);
void PesquisaPorChaveCalculaRelevancia(TipoChave k, TipoArvore t,TipoRelevancia* vetRel,int *comparacoesPesquisa);