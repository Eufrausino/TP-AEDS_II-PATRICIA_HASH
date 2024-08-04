all: src/main.c src/ArquivosC/FormataTexto.c src/ArquivosC/Ocorrencias.c src/ArquivosC/patricia.c src/ArquivosC/ProcessaArquivo.c src/ArquivosC/TAD_HASH.c src/ArquivosC/Relevancia.c
	gcc src/main.c -o exec src/ArquivosC/FormataTexto.c src/ArquivosC/Ocorrencias.c src/ArquivosC/patricia.c src/ArquivosC/ProcessaArquivo.c src/ArquivosC/TAD_HASH.c src/ArquivosC/Relevancia.c
	
run: ./exec
