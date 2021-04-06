/*
Faça um programa que leia um valor N. Este N será o tamanho de um vetor X[N].
A seguir, leia cada um dos valores de X, encontre o menor elemento deste vetor e a 
sua posição dentro do vetor, mostrando esta informação.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	int n;
	scanf("%d", &n);
	int x[n], menor = 1000, pos;
	if (n > 1 && n <= 1000) {
		for (int i = 0; i < n; i++) {
			scanf(" %d", &x[i]);
			if (x[i] <= menor) {
				menor = x[i];
				pos = i;
			}	
		}
		printf("Menor valor: %d\n", menor);
		printf("Posicao: %d\n", pos);
	}

	return 0;
}