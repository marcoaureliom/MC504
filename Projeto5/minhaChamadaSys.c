#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {

	int usuarioId, peso;
	char resp;

	printf("Seja bem-vind@!\n");

	while(1){
		printf("Digite 'o' para obter o peso de um usuário, ou\nDigite 'd' para definir um peso para um usuário, ou\nDigite 's' para sair.\n");
		scanf("\n%c", &resp);

		if(resp=='d' || resp=='o'){

			printf("Digite o uid do usuário: ");
			scanf("%d", &usuarioId);

		}


		if(resp=='d'){

			printf("Digite o peso a ser definido para o usuário: ");
			scanf("%d", &peso);

			if (syscall(385, usuarioId, peso))
				printf("\nNão foi possível definir o peso %d para o usuário de uid=%d.\n", peso, usuarioId);
			else
				printf("\nPeso %d para o usuário de uid=%d definido.\n", peso, usuarioId);
			
		}else if(resp=='o'){

			printf("\nO peso definido para o usuário de uid=%d é %ld.\n", usuarioId, syscall(384, usuarioId));
			
		}else if(resp=='s'){
			printf("Até mais!\n");
			break;
		}

		printf("\n");
	}
	
	return 0;
}
