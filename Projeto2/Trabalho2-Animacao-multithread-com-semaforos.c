//Marco Aurélio de Oliveira Martins.
//Problema dos Leitores/Escritores - Animação AmoungUs

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define nJogadores 5

//Principais variáveis
int jujubas = 5, leitoresContador = 0, nInocentes = nJogadores-1, nImpostores = 1;
sem_t mutex, escritorLock, impressaoLock;

//Vetores que informam onde cada jogador/escritor/leitor/thread está. 
//A posição do jogador N (0..nJogadores-1) nos vetores recebe 1 ou 0.
int jogadorEsperandoNoCorredorParaEntrar[nJogadores],
	jogadorNaSala[nJogadores],
	jogadorForaDaSala[nJogadores];

//Função auxiliar para imprimir os números dos jogadores de A a B na tela (número acima da cabeça do bonequinho)
void imprimaNumeroJogadores(int a, int b, int jogadores[]){
	
	int i, cont=0; int idJogadores[nJogadores];
	for(i=a; i<b; i++)
		if(jogadores[i])
			idJogadores[cont++]=i;
		
	
	for(i=0; i<cont; i++)
		printf(" %d  ", idJogadores[i]+1);
	
	for(i=0; i<b-a-cont; i++)
		printf("    ");

}

//Função auxiliar para imprimir as cabeças e mãos dos jogadores de A a B na tela (cabeça e braços do bonequinho)
void imprimaMaozinhasJogadores(int a, int b, int jogadores[]){
	
	int i, cont=0;
	for(i=a; i<b; i++)
		if(jogadores[i]) cont++;
	
	for(i=0; i<cont; i++)
		printf("\\ü/ ");
	
	for(i=0; i<b-a-cont; i++)
		printf("    ");
	
}

//Função auxiliar para imprimir as pernas dos jogadores de A a B na tela (pernas do bonequinho)
void imprimaPesJogadores(int a, int b, int jogadores[]){
	
	int i, cont=0;
	for(i=a; i<b; i++)
		if(jogadores[i]) cont++;
	
	for(i=0; i<cont; i++)
		printf("/ \\ ");
	
	for(i=0; i<b-a-cont; i++)
		printf("    ");
	
}

//Função para imprimir o estado atual, como se fosse um frame.
//Recebe como parâmetro o código do tipo da atualização a ser realizada e o id do jogador/escritor/leitor/thread
void atualizeFrame(int cod, int id){
	
	sem_wait(&impressaoLock);
	//Início da região crítica
	
	//Imprima o título da animação
	printf("▄▀█ █▀▄▀█ █▀█ █░█ █▄░█ █▀▀   █░█ █▀   ▄▄   ░░█ █░█ ░░█ █░█ █▄▄ ▄▀█ █▀\n");
	printf("█▀█ █░▀░█ █▄█ █▄█ █░▀█ █▄█   █▄█ ▄█   ░░   █▄█ █▄█ █▄█ █▄█ █▄█ █▀█ ▄█\n\n");
		
	if(cod==0){
		//Jogador está próximo da sala
	
		jogadorForaDaSala[id] = 0;
		jogadorEsperandoNoCorredorParaEntrar[id]=1;
		printf("Jogador número %d está por perto:\n", id+1);
	
	}else if(cod==1){
		//Jogador entrou na sala
		
		jogadorForaDaSala[id] = 0;
		jogadorEsperandoNoCorredorParaEntrar[id]=0;
		jogadorNaSala[id]=1;
		printf("Jogador número %d entra na sala e vê que há %d jujubas no pote:\n", id+1, jujubas);
	
	}else if(cod==2){
		//Jogador saiu da sala
		
		jogadorNaSala[id]=0;
		jogadorForaDaSala[id]=1;
		printf("Jogador número %d sai da sala:\n", id+1);

	}else
		//Quando o código é inválido, não atualize nada, apenas imprima:
		printf("Visão geral da sala:\n");
		
		
	//Impressão da planta próximo à sala
	//Desculpe o jeito que mantive as linhas de código abaixo
	//É o melhor que encontrei e que me ajuda a visualizar a impressão.
	printf("▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n");
	printf("█   ▄▄▄▄▄▄▄▄▄▄▄     █\n");
	printf("█   █ Jujubas ░     █    "); imprimaNumeroJogadores(0, nJogadores, jogadorForaDaSala); 				printf("          █\n");
	printf("█   ░   ~%d~   █     █    ", jujubas); imprimaMaozinhasJogadores(0, nJogadores, jogadorForaDaSala); printf("          █\n");
	printf("█   █▄▄▄▄▄▄▄▄▄█     █    "); imprimaPesJogadores(0, nJogadores, jogadorForaDaSala); 				printf("          █\n");
	
	printf("█ "); imprimaNumeroJogadores(0, 3, jogadorNaSala); 	  printf("      █                                  █\n");
	printf("█ "); imprimaMaozinhasJogadores(0, 3, jogadorNaSala); printf("      █                   █              █\n");
	printf("█ "); imprimaPesJogadores(0, 3, jogadorNaSala); 	  printf("      █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█              █\n");
	
	printf("█                      █    "); 											  imprimaNumeroJogadores(0, nJogadores, jogadorEsperandoNoCorredorParaEntrar); 		  printf("       █\n");
	printf("█ ");imprimaNumeroJogadores(3, 5, jogadorNaSala);	printf("             ░    "); imprimaMaozinhasJogadores(0, nJogadores, jogadorEsperandoNoCorredorParaEntrar); printf("       █\n");
	printf("█ ");imprimaMaozinhasJogadores(3, 5, jogadorNaSala);printf("             ░    "); imprimaPesJogadores(0, nJogadores, jogadorEsperandoNoCorredorParaEntrar); 	  printf("       █\n");
	printf("█ ");imprimaPesJogadores(3, 5, jogadorNaSala);  	printf("             ░                               █\n");
	
	printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n\n\n\n\n");
	
	//Espere 2 segundos. 
	//(Para a cena parecer um frame mesmo, embora seja tudo impresso uma coisa embaixo da outra.)
	sleep(2);
	
	//Fim da região crítica
	sem_post(&impressaoLock);
}

//A função do leitor do problema escritores/leitores
void *leitor(void *idP){
	
	int id, i;
	id = (int) idP;
	
	//Aguarde 0 ou 1 segundo 
	//(isso ajuda a criar ordens de threads que ilustrem melhor o problema escritores/leitores)
	sleep(rand()%1);

	//Para parecer algo mais natural estilo amoung us, faço com que a thread entre duas vezes na região crítica,
	//cada uma das vezes após dois segundos.
	for(i=0; i<2; i++, sleep(2)){
	
		//Jogador espera para entrar na sala
		atualizeFrame(0, id);
		
		sem_wait(&mutex);
		
		leitoresContador++;
		if(leitoresContador == 1)
			sem_wait(&escritorLock);
		
		sem_post(&mutex);
		//Início da região crítica para o leitor
				
		//Jogador entra na sala
		atualizeFrame(1, id);
	
		//O jogador/thread ficará parada por 1 segundo na região crítica
		//(isso ajuda a criar ordens de threads que ilustrem melhor o problema escritores/leitores)
		sleep(1);
		
		//Jogador sai da sala
		atualizeFrame(2, id);
		
		//Fim da região crítica para o leitor
		sem_wait(&mutex);
		leitoresContador--;
		
		if(leitoresContador == 0)
			sem_post(&escritorLock);
		
		sem_post(&mutex);
	}
}

//A função do escritor do problema escritores/leitores
void *escritor(void *idP){
	
	int id, i;
	id = (int) idP;
	
	//Para parecer algo mais natural estilo amoung us, faço com que a thread entre duas vezes na região crítica,
	//cada uma das vezes após dois segundos.
	for(i=0; i<2; i++, sleep(2)){
		
		//Jogador espera para entrar na sala
		atualizeFrame(0, id);
		
		sem_wait(&escritorLock);
		//Início da região crítica
		
		//Jogador entra na sala
		atualizeFrame(1, id);
		
		jujubas--;
		//printf("Jogador número %d tranca a sala e, sozinho, come uma jujuba do pote. Restam %d.\n\n\n\n", id+1, jujubas);
		
		//Jogador sai da sala
		atualizeFrame(2, id);
		
		//Fim da região crítica
		sem_post(&escritorLock);
		
	}
}

//Função principal e a que cria as threads
int main(){
	
	long long i;
	//Inicialize os vetores que informam a localidade de cada jogador.
	for(i=0;i<nJogadores;i++)
		jogadorEsperandoNoCorredorParaEntrar[i] = jogadorNaSala[i] = 0, 
		jogadorForaDaSala[i] = 1;
	
	//Crie dois vetores de pthreads
	pthread_t pthreadLeitor[nInocentes], pthreadEscritor[nImpostores], impressao;
	
	//Inicialize os semáforos
	sem_init(&mutex,0,1);
	sem_init(&escritorLock,0,1);
	
	sem_init(&impressaoLock,0,1);
	
	//Exiba o estado inicial da animação
	atualizeFrame(-1, 0);
	
	//Crie nInocentes pthreads que serão leitores/jogadores
	for(i=0;i<nInocentes;i++)
		pthread_create(&pthreadLeitor[i],NULL,leitor,(void *)i+1);
	
	i=0;
	//Crie uma pthreads que será o escritor/impostor
	pthread_create(&pthreadEscritor[i],NULL,escritor,(void *)i);
	
	//Espere as threads terminarem
	for(i=0;i<nImpostores;i++)
		pthread_join(pthreadEscritor[i],NULL);
	
	for(i=0;i<nInocentes;i++)
		pthread_join(pthreadLeitor[i],NULL);

	
	return 0;
}