#include <stdio.h>
#include <stdlib.h>

int main() {
  int num;
  while(1) {
    printf("Digite um valor: ");
    scanf("%d", &num);

    if(num >= 0) {
      int cont = 0;
      for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
          cont++;
        }
      }
      if (cont == 2) {
        printf("%d é primo\n", num);
      } else {
        printf("%d não é primo\n", num);
      }
    } else {
      break;
    }
  }
}