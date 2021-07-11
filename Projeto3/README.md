# Problema dos Leitores/Escritores - Agora usando mutex e semáforo
## Animação Among Us - Jujubas

![image](https://user-images.githubusercontent.com/6686318/125179664-b7e5d880-e1c6-11eb-9362-727ca2427d14.png)


## Descrição do Problema dos Leitores/Escritores

Imagine que você tenha um problema onde em um sistema uma estrutura de dados pode ser acessada simultaneamente para realizar a leitura, porém você deve impedir que essa leitura aconteça simultaneamente a uma edição de um dado, e assim evitar que haja uma leitura inconsistente ou inválida. 

Podem ocorrer várias leituras simultaneamente na então chamada seção crítica; porém, na edição, o recurso não deve estar compartilhado; de modo que você coloque as seguintes condições:

* Qualquer número de leitores pode estar na seção crítica simultaneamente.
* Os escritores devem ter acesso exclusivo à seção crítica.

Este é o chamado “Problema dos Leitores/Escritores”. Onde, enquanto houver leitores, quem pretende escrever deve aguardar; e quem deseja ler, pode ler se ninguém estiver escrevendo, caso contrário deve aguardar.


### Usando semáforos para o Problema dos Leitores/Escritores 

Podemos resolver esse problema com os seguintes algoritmos para

* Escritores:

![image](https://user-images.githubusercontent.com/6686318/118742390-b0d5c600-b826-11eb-84f8-03765be2e018.png)

* Leitores:

![image](https://user-images.githubusercontent.com/6686318/118742399-b501e380-b826-11eb-8abb-99c6bd7f1257.png)

(Imagens retiradas de “[The Little Book of Semaphores](https://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf)” (2.2.1), por Allen B. Downey.)


## Descrição da Animação Among Us - Jujubas

Para realizar a animação em `código C` do Problema dos Leitores/Escritores, decidi adaptar um enredo do jogo chamado de Among Us. Neste jogo, existem N participantes abordo de uma espaçonave, sendo ao menos um deles o chamado Impostor. 
Este jogador-impostor, é sorteado pelo sistema e seu objetivo no jogo é realizar tarefas que sabotem a equipe sem que ninguém desconfie dele, enquanto que os demais devem prezar pelo bem-estar da nave circulando entre as diversas salas. Se porventura descobrirem um impostor, devem decidir numa reunião quem jogarão para fora da espaçonave, trocando informações sobre o que cada um viu, considerando também que o Impostor provavelmente vai mentir.

Ou seja: neste jogo, o Impostor deve realizar suas sabotagens nas diversas salas da espaçonave sem que ninguém veja sua ação. Quando necessário, ele pode trancar a sala que ele estiver (e claro que isso seria suspeito).

* Para a animação, considero que o Impostor é o escritor do Problema Escritor/Leitor, enquanto que os demais participantes são os leitores. 
* Também considero para a animação que o objetivo do Impostor é comer as jujubas que foram guardadas numa sala. Claro, são jujubas espaciais.
* E também considero que o impostor sempre tranca a porta para comer uma jujuba sem que ninguém o veja.

Neste `código em C`, foram usadas as bibliotecas `pthread.h` e `semaphore.h`. Também, foram criadas 5 pthreads, onde 1 representa o Impostor/escritor e as outras representam os demas  jogadores/leitores.

## Adaptação para o Trabalho 03

Na implementação, troquei um dos semáforos do algoritmo do livro por mutex lock (`pthread_mutex_lock(&mutex)`, na função do leitor), assim como adicionei outro mutex lock (`pthread_mutex_lock(&mutexAtualizaFrame)`) para a função que atualiza e imprime a planta (`atualizeFrame()`) da sala com a posição/localização de cada jogador/escritor/leitor, para assim evitar que duas threads a acessasse ao mesmo tempo.

Também, optei por usar alguns comandos `sleep()`, para conseguir alcançar um estado que ilustrasse melhor o momento em que o escritor aguarda leitores saírem da sala, e outro momento onde leitores aguardam o escritor editar o dado, onde a sala encontra-se trancada.

## Observação sobre a animação

Repare que o Impostor é o `jogador 1`. Não optei por deixar claro na animação porque justamente revelaria o segredo.
