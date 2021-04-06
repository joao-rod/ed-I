#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

int main() {
	srand(time(NULL));
	char nomes[30][100], aux[100], letra;
	int cont = 0, sort;

	printf("------------------------\n");
	printf("-----------JOGO---------\n");
	printf("------------------------\n");
	printf("Regras: No max 30 nomes, para parar digite 'fim'\n");
	printf("Para começar aperte qualquer tecla\n");
	system("read b");
	printf("Primeiro digite alguns nomes para jogar\n");

	do {
		scanf(" %[^\n]s", aux);
		if(!strcmp(aux, "fim"))
			break;

		strcpy(nomes[cont],aux);
		cont++;
		if(cont == 30){
			printf("Você chegou ao limite, aperte uma tecla para jogar!\n");
			system("read b");
			break;
		}
	}while(1); 

	cont *= 2;
	int auxCont = 0, position = 0;
	int tentativa1, tentativa2;
	int vet[cont];
	char auxNomes[cont][100];
	char nomesAcertos[cont][100];

	int status;
	for (int i = 0; i < cont; ++i) {
		do {
			vet[i] = rand() % cont;
			status = 0;
			for (int j = 0; j < i; ++j)
				if (vet[i] == vet[j])
					status = 1;
		} while (status);

		for(int x = position; x < cont / 2; x++){
			strcpy(auxNomes[vet[i]], nomes[x]);
			auxCont++;
			break;
		}

		if(auxCont == 2) {
			auxCont = 0;
			position++;
		}
	}

	auxCont = 0;
	position = 1;
	sort = 0;

  while(1) {
		system("clear");
		printf("JOGANDO...\n");
    for(int i=0; i < cont; i++) {
			status = 1;
      for(int j = 0; j < cont; j++){	
				if(!strcmp(nomesAcertos[i], auxNomes[j])) {
					status = 0;
					printf("%d: [%s]\n", i, auxNomes[j]);
					break;
				}
			}
			if(status) 
				printf("%d\n", i);	
    }

		if(position == 0){
			printf("%s\n", aux);
			strcpy(aux, " ");
			position = 1;
			system("read b");
		}else {
			if(auxCont == cont / 2){
				printf("Parabés você ganhou depois de %d rodadas!\n", sort);
				break;
			}
			
			printf("Digite um primeiro valor: ");
			scanf(" %d", &tentativa1);
			system("clear");
			
			printf("JOGANDO...\n");
			for(int i=0; i < cont; i++){
				status = 1;
				for(int j = 0; j < cont; j++){	
					if(!strcmp(nomesAcertos[i], auxNomes[j])) {
						status = 0;
						printf("%d: [%s]\n", i, auxNomes[j]);
						break;
					}
				}
				if(i == tentativa1){
					printf("%d: [%s]\n", i, auxNomes[tentativa1]);
					continue;
				}
				if(status) 
					printf("%d\n", i);	
			}

			printf("Digite um segundo valor: ");
			scanf(" %d", &tentativa2);
			system("clear");

			printf("JOGANDO...\n");
			for(int i=0; i < cont; i++){
				status = 1;
				for(int j = 0; j < cont; j++){	
					if(!strcmp(nomesAcertos[i], auxNomes[j])) {
						status = 0;
						printf("%d: [%s]\n", i, auxNomes[j]);
						break;
					}
				}
				if(i == tentativa1){
					printf("%d: [%s]\n", i, auxNomes[tentativa1]);
					continue;
				}else if(i == tentativa2){
					printf("%d: [%s]\n", i, auxNomes[tentativa2]);
					continue;
				}

				if(status) 
					printf("%d\n", i);	
			}

			status = 1;
			sort++;

			if(tentativa1 > cont || tentativa2 > cont){
				strcpy(aux, "Digite um número válido!");
				status = 0;
				position = 0;
			}else if(!strcmp(auxNomes[tentativa1], nomesAcertos[tentativa1]) || !strcmp(auxNomes[tentativa2],nomesAcertos[tentativa2]) ) {
				status = 0;
				position = 0;
				strcpy(aux, "Você já acertou esse par!");
			}else if(tentativa1 == tentativa2) {
				status = 0;
				position = 0;
				strcpy(aux, "Digite um número válido!");
			}

			if(status) {
				if(!(strcmp(auxNomes[tentativa1], auxNomes[tentativa2]))){
					auxCont++;
					position = 0;
					strcpy(aux, "Parabéns, você acertou!");
					strcpy(nomesAcertos[tentativa1], auxNomes[tentativa1]);
					strcpy(nomesAcertos[tentativa2], auxNomes[tentativa1]);
				}else {
					printf("Você errou, tente novamente!\n");
					system("read b");
				}
			}
		}
	}

	return 0;
}