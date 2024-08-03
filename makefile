all: src/mainPatricia.c src/ArquivosC/FormataTexto.c src/ArquivosC/Ocorrencias.c src/ArquivosC/patricia.c src/ArquivosC/ProcessaArquivo.c src/ArquivosC/TAD_HASH.c 
	gcc src/mainPatricia.c -o exec src/ArquivosC/FormataTexto.c src/ArquivosC/Ocorrencias.c src/ArquivosC/patricia.c src/ArquivosC/ProcessaArquivo.c src/ArquivosC/TAD_HASH.c
	
run: ./exec
