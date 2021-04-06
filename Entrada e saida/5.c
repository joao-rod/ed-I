#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	int n, sort, maior = 0, menor = 100;
	float media = 0;

	printf("Quantidade de valores a sortear: ");
	scanf("%d", &n);

	if (n > 0 && n <= 100) {
		for (int i = 0; i < n; i++) {
			sort = rand() % n + 1;
			printf("%d\t", sort);
			if(sort >= maior) {
				maior = sort;
			}
			if (sort <= menor) {
				menor = sort;
			}
			media += sort;
		}
		printf("\nO menor valor é: %d\n", menor);
		printf("O maior valor é: %d\n", maior);
		printf("A media simples é de: %.2f\n", media / n);
	} else {
		printf("Digite um valor no intervalo de 0 a 100...\n");
	}
}
