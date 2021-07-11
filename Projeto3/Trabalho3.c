//Marco Aurélio de Oliveira Martins.
//Problema dos Leitores/Escritores - Animação Among Us
//Agora usando mutex e semáforo

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

//Define a quantidade de pthreads criadas
#define nJogadores 5

//Principais variáveis
int jujubas = 5, leitoresContador = 0, impostorTrancouSala = 0, nInocentes = nJogadores-1, nImpostores = 1;
sem_t escritorLock;
pthread_mutex_t mutex, mutexAtualizaFrame;

//Vetores que informam onde cada jogador/escritor/leitor/thread está. 
//A posição do jogador N (0..nJogadores-1) nos vetores recebe 1 ou 0.
int jogadorEsperandoNoCorredorParaEntrar[nJogadores],
	jogadorNaSala[nJogadores],
	jogadorForaDaSala[nJogadores];

//Função auxiliar de atualizeFrame() para imprimir os números dos jogadores de A a B na tela (número acima da cabeça do bonequinho)
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

//Função auxiliar de atualizeFrame() para imprimir as cabeças e mãos dos jogadores de A a B na tela (cabeça e braços do bonequinho)
void imprimaMaozinhasJogadores(int a, int b, int jogadores[]){
	
	int i, cont=0;
	for(i=a; i<b; i++)
		if(jogadores[i]) cont++;
	
	for(i=0; i<cont; i++)
		printf("\\ü/ ");
	
	for(i=0; i<b-a-cont; i++)
		printf("    ");
	
}

//Função auxiliar de atualizeFrame() para imprimir as pernas dos jogadores de A a B na tela (pernas do bonequinho)
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
	
	//Imprima o título da animação	
	printf("▄▀█ █▀▄▀█ █▀█ █▄░█ █▀▀   █░█ █▀   ▄▄   ░░█ █░█ ░░█ █░█ █▄▄ ▄▀█ █▀\n");
	printf("█▀█ █░▀░█ █▄█ █░▀█ █▄█   █▄█ ▄█   ░░   █▄█ █▄█ █▄█ █▄█ █▄█ █▀█ ▄█\n\n");

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

	}else if(cod==3){
		//Jogador come jujuba da sala
		printf("Jogador número %d tranca a sala e, sozinho, come uma jujuba do pote. Restam %d jujubas:\n", id+1, jujubas);
	
	}else if(cod==4){
		//Jogador destranca e dai da sala
		jogadorNaSala[id]=0;
		jogadorForaDaSala[id]=1;
		printf("Jogador número %d destranca e sai da sala:\n", id+1);
	
	}else
		//Quando o código é inválido, não atualize nada, apenas imprima:
		printf("Visão geral da sala:\n");
		
		
	//Impressão da planta próximo à sala
	//Desculpe o jeito que mantive as linhas de código abaixo
	//É o melhor que encontrei e que me ajuda a visualizar a impressão pelo meu editor de texto.
	printf("▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n");
	printf("█   SALA PRINCIPAL   █ SAÍDA █                          █\n");
	printf("█   ▄▄▄▄▄▄▄▄▄▄▄              █                          █\n");
	printf("█   █ Jujubas ░              █    "); imprimaNumeroJogadores(0, nJogadores, jogadorForaDaSala); 				printf("  █\n");
	printf("█   ░   ~%d~   █              █    ", jujubas); imprimaMaozinhasJogadores(0, nJogadores, jogadorForaDaSala); printf("  █\n");
	printf("█   █▄▄▄▄▄▄▄▄▄█      █       █    "); imprimaPesJogadores(0, nJogadores, jogadorForaDaSala); 				printf("  █\n");
	printf("█ "); imprimaNumeroJogadores(0, 3, jogadorNaSala); 	  printf("       █                                  █\n");
	printf("█ "); imprimaMaozinhasJogadores(0, 3, jogadorNaSala); printf("       █                       █          █\n");
	printf("█ "); imprimaPesJogadores(0, 3, jogadorNaSala); 	  printf("       █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█          █\n");
	printf("█                       █    "); 											  imprimaNumeroJogadores(0, nJogadores, jogadorEsperandoNoCorredorParaEntrar); 		  printf("       █\n");
	printf("█ ");imprimaNumeroJogadores(3, 5, jogadorNaSala);	if(impostorTrancouSala)printf("              ░    ");else printf("                   "); imprimaMaozinhasJogadores(0, nJogadores, jogadorEsperandoNoCorredorParaEntrar); printf("       █\n");
	printf("█ ");imprimaMaozinhasJogadores(3, 5, jogadorNaSala);if(impostorTrancouSala)printf("              ░    ");else printf("                   "); imprimaPesJogadores(0, nJogadores, jogadorEsperandoNoCorredorParaEntrar); 	  printf("       █\n");
	printf("█ ");imprimaPesJogadores(3, 5, jogadorNaSala);  	if(impostorTrancouSala)printf("      ENTRADA ░    ");else printf("      ENTRADA      "); printf("                           █\n");
	printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n\n\n\n\n");
	
	//Espere 2 segundos. 
	//(Para a cena parecer um frame mesmo, embora seja tudo impresso uma coisa embaixo da outra.)
	sleep(2);
	
}

//A função do leitor do problema escritores/leitores
void *leitor(void *idP){
	
	int id, i;
	id = *(int*) idP;
	
	//Aguarde 0 ou 1 segundo 
	//(isso ajuda a criar ordens de threads que ilustrem melhor o problema escritores/leitores)
	sleep(rand()%1);

	//Para parecer algo mais natural estilo Among Us, faço com que a mesma thread/pessoa entre duas vezes na região crítica,
	//cada uma das vezes após dois segundos.
	for(i=0; i<2; i++, sleep(2)){
		
		pthread_mutex_lock(&mutexAtualizaFrame);
		atualizeFrame(0, id); //Jogador espera para entrar na sala
		pthread_mutex_unlock(&mutexAtualizaFrame);
	
		//Leitor adquire o bloqueio antes de modificar o leitoresContador
		pthread_mutex_lock(&mutex);
		leitoresContador++;
		
		if(leitoresContador == 1)
			//Se for o primeiro leitor, então ele deve bloquear a entrada o escritor
			sem_wait(&escritorLock);
		
		pthread_mutex_unlock(&mutex);
		//Início da região crítica para o leitor
		
		pthread_mutex_lock(&mutexAtualizaFrame);		
		atualizeFrame(1, id); //Jogador entra na sala
		pthread_mutex_unlock(&mutexAtualizaFrame);
	
		//O jogador/thread ficará parada por 1 segundo na região crítica
		//(isso ajuda a criar ordens de threads que ilustrem melhor o problema escritores/leitores)
		sleep(1);
		
		//Fim da região crítica para o leitor
		//Leitor adquire o bloqueio antes de modificar o leitoresContador
		pthread_mutex_lock(&mutex);
		leitoresContador--;
		
		pthread_mutex_lock(&mutexAtualizaFrame);
		atualizeFrame(2, id); //Jogador sai da sala
		pthread_mutex_unlock(&mutexAtualizaFrame);
		
		if(leitoresContador == 0)
			//Se for o último leitor, deve acordar o escritor
			sem_post(&escritorLock);
		
		pthread_mutex_unlock(&mutex);
	}
}

//A função do escritor do problema escritores/leitores
void *escritor(void *idP){
	
	int id, i;
	id = *(int*) idP;
	
	sleep(2);
	
	//Para parecer algo mais natural estilo Among Us, faço com que a mesma thread entre duas vezes na região crítica,
	//cada uma das vezes após dois segundos.
	for(i=0; i<2; i++, sleep(2)){
		
		pthread_mutex_lock(&mutexAtualizaFrame);
		//Jogador espera para entrar na sala
		atualizeFrame(0, id);
		pthread_mutex_unlock(&mutexAtualizaFrame);
		
		pthread_mutex_lock(&mutexAtualizaFrame);
		//Jogador entra na sala
		atualizeFrame(1, id);
		pthread_mutex_unlock(&mutexAtualizaFrame);
		
		//Início da região crítica
		sem_wait(&escritorLock);
		
		pthread_mutex_lock(&mutexAtualizaFrame);
		impostorTrancouSala=1;
		jujubas--;
		atualizeFrame(3, id);
		pthread_mutex_unlock(&mutexAtualizaFrame);
		
		sleep(1);
		
		pthread_mutex_lock(&mutexAtualizaFrame);
		impostorTrancouSala=0;
		//Jogador sai da sala
		atualizeFrame(4, id);
		pthread_mutex_unlock(&mutexAtualizaFrame);
		
		//Fim da região crítica
		sem_post(&escritorLock);
		
	}
}

//Função principal e a que cria as threads
int main(){
	
	long long i, j;
	
	//Inicialize os vetores que informam a localidade de cada jogador no mapa.
	for(i=0;i<nJogadores;i++)
		jogadorEsperandoNoCorredorParaEntrar[i] = jogadorNaSala[i] = 0, 
		jogadorForaDaSala[i] = 1;
	
	//Crie dois vetores de pthreads
	pthread_t pthreadLeitor[nInocentes], pthreadEscritor[nImpostores];
	
	//Inicialize mutex
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutexAtualizaFrame, NULL);
	
	//Inicialize o semáforo
	sem_init(&escritorLock,0,1);
		
	//Exiba o estado inicial da animação
	atualizeFrame(-1, 0);
	
	//Vetor para identificação dos impostores e inocentes (escritores e leitores, respectivamente)
	int id[nInocentes+nImpostores];
	for(i=0;i<nJogadores;i++)
		id[i] = i;
	
	
	//Crie uma pthread que será o escritor/impostor
	for(i=0;i<nImpostores;i++)
		pthread_create(&pthreadEscritor[i],NULL,escritor,(void *)&id[i]);
	
	//Crie nInocentes pthreads que serão leitores/jogadores
	for(i=0;i<nInocentes;i++)
		pthread_create(&pthreadLeitor[i],NULL,leitor,(void *)&id[i+nImpostores]);
	
	//Espere as threads terminarem
	for(i=0;i<nImpostores;i++)
		pthread_join(pthreadEscritor[i],NULL);
	
	for(i=0;i<nInocentes;i++)
		pthread_join(pthreadLeitor[i],NULL);

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutexAtualizaFrame);
    sem_destroy(&escritorLock);
	
	return 0;
}