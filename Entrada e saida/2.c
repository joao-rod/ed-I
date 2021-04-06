#include <stdio.h>
#include <stdlib.h>

int main() {
	int n;

	//Entrada de dados
	printf("Digite uma valor: ");
	scanf("%d", &n);

	//Fatorando o valor
	printf("%d nota(s) de 100\n", n / 100);
	n = n - n / 100 * 100;

	printf("%d nota(s) de 50\n", n / 50);
	n = n - n / 50 * 50;

	printf("%d nota(s) de 20\n", n / 20);
	n = n - n / 20 * 20;

	printf("%d nota(s) de 10\n", n / 10);
	n = n - n / 10 * 10;

	printf("%d nota(s) de 5\n", n / 5);
	n = n - n / 5 * 5;

	printf("%d nota(s) de 2\n", n / 2);
	n = n - n / 2 * 2;

	printf("%d nota(s) de 1\n", n / 1);
	n = n - n / 1 * 1;
}
