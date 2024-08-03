#include "../Header/FormataTexto.h"

// Função para converter uma string para minúsculas
void toLowerCase(char *str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

// Função para remover espaços extras e retirar ponto final
char *trim_whitespace(char *str) {
    char *end;

    // Remover espaços à esquerda
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // Todos os caracteres são espaços?
        return str;

    // Remover espaços à direita
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Remover ponto final, se houver (para ingrediente final)
    if (*end == '.') {
        end--;
    }

    // Adicionar terminador nulo
    end[1] = '\0';

    return str;
}

// Função auxiliar para ler uma palavra da entrada padrão (ziviani)
void LerPalavra(char *p, int Tam) {
    char c;
    int i, j;
    fflush(stdin);
    j = 0;
    while (((c = getchar()) != '\n') && j < Tam - 1) {
        p[j++] = c;
    }
    p[j] = '\0';
    while (c != '\n') {
        c = getchar();
    }

    // Desconsiderar espaços ao final da cadeia
    for (i = j - 1; (i >= 0 && p[i] == ' '); i--) {
        p[i] = '\0';
    }
}