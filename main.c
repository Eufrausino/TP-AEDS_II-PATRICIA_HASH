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
	return 0;
}