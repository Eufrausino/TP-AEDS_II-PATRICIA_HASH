#include "patricia.h"
int main(int argc, char *argv[]){
	TipoArvore a = NULL;

	//Insere cada chave na arvore

	TipoChave string1 = "casa de vo";
	a = Insere(string1, &a);
	TipoChave string2 = "casamento";
	a = Insere(string2, &a);
	TipoChave string3 = "casado";
	a = Insere(string3, &a);
	TipoChave string4 = "amado batista";
	a = Insere(string4, &a);

	TipoChave string5 = "boneca de pano";
	a = Insere(string5, &a);
	TipoChave string6 = "bonito";
	a = Insere(string6, &a);
	TipoChave string7 = "biscoito de chocolate";
	a = Insere(string7, &a);
	TipoChave string8 = "amor";
	a = Insere(string8, &a);

	TipoChave string9 = "duda tinder";
	a = Insere(string9, &a);
	TipoChave string10 = "lua de cristal";
	a = Insere(string10, &a);
	TipoChave string11 = "zumbido";
	a = Insere(string11, &a);
	TipoChave string12 = "xuxa";
	a = Insere(string12, &a);

	Pesquisa(string2, a);

	ImprimeArvore(a);

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