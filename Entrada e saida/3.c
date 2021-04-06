#include <stdio.h>
#include <stdlib.h>

int main() {
	int x, y;

	while (1) {
		printf("Digite um valor para x: ");
		scanf("%d", &x);
		printf("Digite um valor para y: ");
		scanf("%d", &y);

		int soma = 0, x1 = x, y1 = y;

		if(x != 0 && y != 0) {
			if (x < y) {
				for (int i = x; i <= y; i++) {
					soma += x;
					x++;
				}
				printf("Para(%d, %d): %d\n", x1, y1, soma);
			} else {
				for (int i = y; i <= x; i++) {
					soma += y;
					y++;
				}
				printf("Para(%d, %d): %d\n", x1, y1, soma);
			}
		} else {
			break;
		}
	}
}