#include <pthread.h>
#include <stdio.h>
#include <string.h>

//Número de buscas possíveis, total de palavras no vetor "palavras", número de linhas e colunas no tabuleiro.
#define NMOVIMENTOS 8
#define NPALAVRAS 10
#define NCOLUNAS 9
#define NLINHAS 9

//Tabela/tabuleiro
char tabela[NCOLUNAS][NLINHAS] = {
    {'E', 'M', 'M', 'A', 'R', 'G', 'O', 'R', 'P'},
    {'C', 'S', 'U', 'A', 'O', 'N', 'L', 'L', 'D'},
    {'O', 'T', 'N', 'A', 'F', 'I', 'L', 'O', 'I'},
    {'M', 'E', 'L', 'I', 'J', 'G', 'E', 'O', 'K'},
    {'P', 'W', 'H', 'K', 'G', 'G', 'H', 'P', 'Q'},
    {'I', 'C', 'O', 'M', 'P', 'U', 'T', 'E', 'R'},
    {'L', 'L', 'N', 'R', 'Z', 'B', 'L', 'O', 'X'},
    {'E', 'U', 'O', 'M', 'L', 'E', 'Q', 'P', 'U'},
    {'R', 'N', 'I', 'R', 'P', 'D', 'C', 'O', 'E'}
};

//Palavras a serem procuradas
char palavras[NPALAVRAS][20] = {
    "COMPILE", 
	"COMPUTER", 
	"DEBUGGING", 
	"HELLO", 
	"LOOP", 
	"WORLD", 
	"PROGRAMME", 
	"PLUGINS",
	"RUN",
	"GOAL"
};

//Procura palavras que estejam na horizontal da esquerda para a direita.
void* esq_dir(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(i=0; i<NLINHAS; i++)
			for(j=0; j<NCOLUNAS && NCOLUNAS-j>=tam; j++){
				l=0;
				while(l<tam && j+l<NCOLUNAS && tabela[i][j+l]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na horizontal da esquerda para a direita.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

//Procura palavras que estejam na horizontal da direita para a esquerda.
void* dir_esq(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(i=0; i<NLINHAS; i++)
			for(j=NCOLUNAS; j>=0 && j+1>=tam; j--){
				l=0;
				while(l<tam && j-l>=0 && tabela[i][j-l]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na horizontal da direita para a esquerda.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

//Procura palavras que estejam na vertical de cima para baixo.
void* cima_baixo(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(j=0; j<NCOLUNAS; j++)
			for(i=0; i<NLINHAS && NLINHAS-i>=tam; i++){
				l=0;
				while(l<tam && i+l<NLINHAS && tabela[i+l][j]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na vertical de cima para baixo.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

//Procura palavras que estejam na vertical de baixo para cima.
void* baixo_cima(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(j=0; j<NCOLUNAS; j++)
			for(i=NLINHAS; i>=0 && i+1>=tam; i--){
				l=0;
				while(l<tam && i-l>=0 && tabela[i-l][j]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na vertical de baixo para cima.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

//Procura palavras que estejam na diagonal da esquerda para a direita e de cima para baixo.
void* diagonal_esq_dir_cima_baixo(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(i=0; i<NLINHAS; i++)
			for(j=0; j<NCOLUNAS && NCOLUNAS-j>=tam && NLINHAS-i>=tam; j++){
				l=0;
				while(l<tam && j+l<NCOLUNAS && i+l<NLINHAS && tabela[i+l][j+l]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na diagonal da esquerda para a direita e de cima para baixo.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

//Procura palavras que estejam na diagonal da direita para a esquerda e de baixo para cima.
void* diagonal_dir_esq_baixo_cima(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(i=tam-1; i<NLINHAS; i++)
			for(j=NCOLUNAS; j>=0 && j+1>=tam && i+1>=tam; j--){
				l=0;
				while(l<tam && j-l>=0 && i-l>=0 && tabela[i-l][j-l]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na diagonal da direita para a esquerda e de baixo para cima.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

//Procura palavras que estejam na diagonal da direita para a esquerda e de cima para baixo.
void* diagonal_dir_esq_cima_baixo(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(i=0; i<NLINHAS; i++)
			for(j=tam-1; j<NCOLUNAS && NLINHAS-i>=tam; j++){
				l=0;
				while(l<tam && j-l>=0 && i+l<NLINHAS && tabela[i+l][j-l]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na diagonal da direita para a esquerda e de cima para baixo.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

//Procura palavras que estejam na diagonal da esquerda para a direita e de baixo para cima.
void* diagonal_esq_dir_baixo_cima(void *v){
	
	int i, j, k, l, tam;
	for(k=0; k<NPALAVRAS; k++){
		tam = strlen(palavras[k]);
		for(i=tam-1; i<NLINHAS; i++)
			for(j=0; j<NCOLUNAS && NCOLUNAS-j>=tam; j++){
				l=0;
				while(l<tam && j+l<NCOLUNAS && i-l>=0 && tabela[i-l][j+l]==palavras[k][l])
					l++;
					
				if(l==tam)
					printf("Encontrada palavra %s iniciando na posição (%d, %d), na diagonal da esquerda para a direita e de baixo para cima.\n", palavras[k], i+1, j+1);
			}
	}
	
	return NULL;
}

int main() {
	
	int i;
	//Vetor de pthreads
	pthread_t thrMovimentos[NMOVIMENTOS];

	//Crie uma thread para cada modo de busca na tabela/tabuleiro de caça-palavras.
	//Cada thread realiza um movimento de pesquisa diferente na matriz.
	if (pthread_create(&thrMovimentos[0], NULL, esq_dir, NULL))
		fprintf(stderr, "Erro na criação da thread 1. \n");
    
    if (pthread_create(&thrMovimentos[1], NULL, dir_esq, NULL))
		fprintf(stderr, "Erro na criação da thread 2. \n");
	
	if (pthread_create(&thrMovimentos[2], NULL, cima_baixo, NULL))
		fprintf(stderr, "Erro na criação da thread 3. \n");
	
	if (pthread_create(&thrMovimentos[3], NULL, baixo_cima, NULL))
		fprintf(stderr, "Erro na criação da thread 4. \n");
    
	if (pthread_create(&thrMovimentos[4], NULL, diagonal_esq_dir_cima_baixo, NULL))
		fprintf(stderr, "Erro na criação da thread 5. \n");
	
	if (pthread_create(&thrMovimentos[5], NULL, diagonal_dir_esq_baixo_cima, NULL))
		fprintf(stderr, "Erro na criação da thread 6. \n");
	
	if (pthread_create(&thrMovimentos[6], NULL, diagonal_dir_esq_cima_baixo, NULL))
		fprintf(stderr, "Erro na criação da thread 7. \n");
	
	if (pthread_create(&thrMovimentos[7], NULL, diagonal_esq_dir_baixo_cima, NULL))
		fprintf(stderr, "Erro na criação da thread 8. \n");
		
	//Espere as threads terminarem:
	for (i = 0; i < NMOVIMENTOS; i++)
		pthread_join(thrMovimentos[i], NULL);
  
	return 0;
}