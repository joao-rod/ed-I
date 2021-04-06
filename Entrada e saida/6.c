#include <stdio.h>
#include <stdlib.h>

int main() {
  int x, y;

  printf("Digite um valor para x: ");
  scanf("%d", &x);
  printf("Digite um valor para y: ");
  scanf("%d", &y);

  if (x <= y) {
    for (int i = x; i <= y; i++) {
      int cont = 0;
      for (int j = 1; j <= i; j++) {
        if (i % j == 0){
          cont++;
        }
      }
      if (cont == 2){
        printf("%d\t", i);
      }
    }
  } else {
    printf("Valor de X deve ser menor que o valor de Y");
  }
}