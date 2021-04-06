/*
Leia um valor X. Coloque este valor na primeira posição 
de um vetor N[100]. Em cada posição subsequente de N (1 até 99),
coloque a metade do valor armazenado na posição anterior,
conforme o exemplo abaixo. Imprima o vetor N.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	double n[100], x;

	scanf(" %f", &x);
	n[0] = x;

	printf("N[0] = %.4lf\n",n[0]);
	for (int i = 1; i < 100; i++) {
		x = x / 2;
		n[i] = x;
		printf("N[%d] = %.4lf\n", i, n[i]);
	}

	return 0;
}