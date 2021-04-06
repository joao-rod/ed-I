/*
Faça um programa que leia um valor T e preencha um vetor N[1000]
com a sequência de valores de 0 até T-1 repetidas vezes, 
conforme exemplo abaixo. Imprima o vetor N.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	int n[1000], t, cont = 0;

	scanf(" %d", &t);

	if (t >= 2 && t <= 50)
		for (int i = 0; i < 1000; i++) {
			n[i] = cont;
			cont++;
			if (cont == t)
				cont = 0;
			printf("N[%d] = %d\n", i, n[i]);
		}

	return 0;
}