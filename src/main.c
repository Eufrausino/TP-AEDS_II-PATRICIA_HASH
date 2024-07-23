#include <stdio.h>
#include<stdlib.h> 
#include <sys/time.h>
#include "patricia.h"

int main()
{
  int opcao;
  printf("Entre com uma das seguintas opções:\n");
  printf("1)receber o arquivo de entrada com os textos a serem indexados;\n");
  printf("2)construir os índices invertidos, a partir dos textos de entrada, usando os TADs PATRICIA e HASH;\n");
  printf("3)mprimir os índices invertidos, contendo as palavras em ordem alfabética, uma por linha, com suas respectivas listas de ocorrências;\n");
  printf("4)realizar buscas por um ou mais termo(s) de busca, nos índices construídos, individualmente, apresentando os arquivos ordenados por relevância, também individualmente para cada TAD.\n");

  scanf("%d", &opcao);

  switch(opcao)
  {
    case(1):
      break;
    case(2):
      break;
    case(3):
      break;
    case(4):
      break;
    default:
      break;
  }

  return 0;
} 