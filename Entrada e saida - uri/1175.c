/*
Faça um programa que leia um vetor N[20].
Troque a seguir, o primeiro elemento com o último, 
o segundo elemento com o penúltimo, etc., 
até trocar o 10º com o 11º. Mostre o vetor modificado.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	int n[20], aux;
	for (int i = 0; i < 20; i++){
		scanf(" %d", &n[i]);
	}

	for (int i = 0; i < 10; i++){
		aux = n[i];
		n[i] = n[19 - i];
		n[19 - i] = aux;
	}

	for (int i = 0; i < 20; i++){
		printf("N[%d] = %d\n", i, n[i]);
	}

	return 0;
}