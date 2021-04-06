#include <stdio.h>
#include <stdlib.h>

int main() {
	int n1, n2, n3;

	// Entrada de dados
	printf("Digite o 1º valor: ");
	scanf("%d", &n1);
	printf("Digite o 2º valor: ");
	scanf("%d", &n2);
	printf("Digite o 3º valor: ");
	scanf("%d", &n3);

	system("clear");
	int menor, medio, maior;
	
	// Menor valor
	if (n1 < n2 && n1 < n3){
		menor = n1;
	} else if (n2 < n1 && n2 < n3) {
		menor = n2;
	} else {
		menor = n3;
	}

	// Valor do meio
	if ((n1 < n2 && n1 > n3) || (n1 > n2 && n1 < n3)){
		medio = n1;
	} else if ((n2 < n1 && n2 > n3) || (n2 > n1 && n2 < n3)){
		medio = n2;
	} else {
		medio = n3;
	}

	// Maior valor
	if (n1 > n2 && n1 > n3){
		maior = n1;
	} else if (n2 > n1 && n2 > n3) {
		maior = n2;
	} else {
		maior = n3;
	}

	printf("Para(%d, %d, %d) = ", n1, n2, n3);
	printf("%d - %d - %d\n", menor, medio, maior);
}