#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gconio.h>

int main() {
	srand(time(NULL));
	time_t start, end;
	time(&start);

	int vet[9], auxVet[9], number, cont = 0, aux, auxCont = 0;
	int inicio = 0, trinca = 0, auxContSeq = 0, auxContIgual = 0, qntPartidas = 0;
	int vetTrinca[3], soma, auxTrinca, sort = 0, trincaSeq = 0, trincaIgual = 0;
	char info[10];

	puts("");
	system("figlet Pirates");
	puts("");

	for(int i=0; i < 9; i++) {
		vet[i] = 1 + rand() % 13;
		auxVet[i] = 999;
	}
	textcolor(WHITE);

	printf("----------------------------------------------------------------------\n");
	printf("----------------------BEM VINDO AO JOGO DO PIFE-----------------------\n");
	printf("----------------------------------------------------------------------\n");
	puts("");

	while(1) {
		auxContSeq = 1;
		auxContIgual = 1;
		puts("");
		printf("----------------------------------------------------------------------\n");
		for(int i = 0; i < 9; i++) {
			trinca = 0;
			auxCont = 0;
			for(int y = 0; y < 9; y++) {
				if(i == auxVet[y]){
					trinca = 1;
					break;
				}
			}

			if(trinca == 0){
				for(int y = i; y < 9; y ++) {
					if(vet[i] > vet[y]) {
						aux = vet[i];
						vet[i] = vet[y];
						vet[y] = aux;
					}
				}

				printf("[%d]\t", vet[i]);
			}
		}
		printf("\n----------------------------------------------------------------------\n");
		aux = 0;

		for(int i = 0; i < 9; i++) {
			aux++;
			trinca = 0;
			auxCont = 0;
			auxContSeq = 1;
			auxContIgual = 1;
			vetTrinca[0] = i;

			for(int y = 0; y < 9; y++) {
				if(i == auxVet[y]){
					trinca = 2;
					break;
				}
			}

			if(trinca == 2){
				continue;
			}else {
				auxTrinca = vet[i];
				for(int y = i + 1; y < 9; y++) {
          trinca = 0;
					for(int z = 0; z < 9; z++) {
            if(y == auxVet[z]) {
              trinca = 2;
					    break;
            }
          }

          if(trinca == 2)
            continue;
          else {
            if(auxTrinca + 1 == vet[y]) {
              vetTrinca[auxContSeq] = y;
              auxContSeq++;
              auxTrinca = vet[y];
							auxContIgual = 1;
            }else if(vet[i] == vet[y]) {
            	vetTrinca[auxContIgual] = y;
            	auxContIgual++;
            }

            if(auxContIgual == 3){
              auxContSeq = 1;
              auxContIgual = 1;
              trinca = 1;
              cont++;
							trincaIgual++;
              break;
            }else if(auxContSeq == 3) {
              auxContSeq = 1;
              auxContIgual = 1;
              trinca = 1;
              cont++;
							trincaSeq++;
              break;
            }
          }
        }

        if(trinca == 1) {
					printf("\nVocê fez uma trinca, CARTAS: ");
					textcolor(GREEN);
          soma = 3 * (cont - 1);
          for(int j = soma; j < soma + 3; j++) {
						printf("[%d]", vet[vetTrinca[auxCont]]);
            auxVet[j] = vetTrinca[auxCont];
            auxCont++;
          }
					textcolor(WHITE);
        }
			}
		}

		if(cont == 3){
			textcolor(GREEN);
			printf("\n\nPARABÉNS VOCÊ GANHOU!\n");
			break;
		}

		textcolor(BLUE);
		printf("\nDigite a carta que deseja trocar: ");
		scanf(" %d", &number);
		textcolor(WHITE);

		qntPartidas++;
		for(int i = 0; i < 9; i++){
			trinca = 0;
			for(int y = 0; y < 9; y++) {
				if(i == auxVet[y]){
					trinca = 1;
					break;
				}
			}

			if(trinca == 0) {
				if(number == vet[i]) {
					sort = 1 + rand() % 13;
					vet[i] = sort;
					printf("A sua carta foi trocada!\n");
					trinca = number;
					number = 999;
				}
			}

			if(number == 999)
				break;
		}

		if(number != 999) {
			textcolor(RED);		
			printf("\nATENÇÃO! CARTA INVÁLIDA!!\nEsses são seus valores disponíveis...\n");
			textcolor(WHITE);
		}
	}

	time(&end);
	int tempo_s = difftime(end, start);
	int min = tempo_s/60;
	textcolor(WHITE);
	printf("\nDeseja ver informações da partida? [S/N]: ");
	scanf(" %s", info);

	textcolor(BLUE);
	if(!strcmp(info, "S") || !strcmp(info, "s")) {
		puts("");		
		printf("Tempo da partida: %dm e %ds\n", min, tempo_s - (60 * min));
		printf("Quantidade rodadas: %d\n", qntPartidas);
		printf("Total de trincas por cartas iguais: %d\n", trincaIgual);
		printf("Total de trincas por cartas sequenciais: %d\n", trincaSeq);
	}

	return 0;
}	