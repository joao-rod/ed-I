#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
  char nome_titular[100];
  int numero_conta;
  float saldo_bancario;
}Conta;

typedef struct{
  char tipo[100];
  int descricao;
  int conta_origem;
  int conta_destino;
  float valor;
}Movimentacao;

int verificarCod(int cod, int cont, Conta *contas) {
  int status = 0;
  for(int i = 0; i < cont; i++){
    if(contas[i].numero_conta == cod){
      status = 1;
      break;
    }
  }

  return status;
}

int gerarNumeroConta(int cont, Conta *contas) {
  srand(time(NULL));
  int sort;
  while(1) {
    sort = 100 + (rand() % 899);
    if(sort % 7 == 0)
      if(!verificarCod(sort, cont, contas))
        return sort;
  }
}


void printLinha(char carac) {
  for(int i = 0; i < 30; i++)
    printf("%c", carac);

  printf("\n");
}

int contTransac = 0;
char transacoes[100][100];
void criarTransacao(char frase[100]){
  strcpy(transacoes[contTransac], frase); 
  contTransac++;
}

void chamarMenu() {
  puts("");
  printLinha('*');
  printf("1- Cadastro de Conta\n");
  printf("2- Depósito\n");
  printf("3- Saque\n");
  printf("4- Transferência entre contas\n");
  printf("5- Registro Geral de Movimentações\n");
  printf("6- Relatório de Contas\n");
  printLinha('*');
}

void criarConta(int cont, Conta *conta, Conta *contas) {
  puts("");
  printLinha('-');

  int cod = gerarNumeroConta(cont, contas);

  conta->numero_conta = cod;
  printf("Digite um nome: ");
  scanf(" %[^\n]s", conta->nome_titular);

  conta->saldo_bancario = 0;
  printf("Conta criada com sucesso!\n\n");
  printLinha('-');
  puts("");
  
}

void deposito(int cont, Conta *contas){
  if(cont == 0){
    puts("");
    printLinha('#');
    printf("Você precisa ter contas cadastradas!\n\n\n");

    return;
  }

  int cod, status = 0;
  float value;
  printLinha('-');
  printf("Digite o código da conta: ");
  scanf(" %d", &cod);

  if(!verificarCod(cod, cont, contas)) {
    printf("Esse código não existe!\n");
    return;
  }

  printf("Digite o valor de depósito: ");
  scanf(" %f", &value);

  for(int i = 0; i < cont; i++){
    if(contas[i].numero_conta == cod){
      contas[i].saldo_bancario+= value;
      status = 1;
      break;
    }
  }
  criarTransacao("Houve um deposito!");

  printf("Depósito efetuado com sucesso!\n");
  printLinha('-');
}

void saque(int cont, Conta *contas){
  if(cont == 0){
    puts("");
    printLinha('#');
    printf("Você precisa ter contas cadastradas!\n\n\n");
    return;
  }

  int cod, status = 0;
  float value;
  printLinha('-');
  printf("Digite o código da conta para saque: ");
  scanf(" %d", &cod);

  if(!verificarCod(cod, cont, contas)) {
    printf("Esse código não existe");
    return;
  }

  printf("Digite o valor de saque: ");
  scanf(" %f", &value);

  for(int i = 0; i < cont; i++){
    if(contas[i].numero_conta == cod){
      if(contas[i].saldo_bancario < value){
        printf("Você excedeu o valor que tem em caixa!\n");
        return;
      }
      contas[i].saldo_bancario-= value;
      break;
    }
  }

  criarTransacao("Houve um saque");

  printf("Saque efetuado com sucesso!\n");
  printLinha('-');
}

void transferencia(int cont, Conta *contas) {
  if(cont < 2 ){
    puts("");
    printLinha('#');
    printf("Você precisa ter no mínimo duas contas cadastradas para efetuar uma transferência!\n\n\n");
    return;
  }

  int origem, destino, status = 0;
  float value;
  printLinha('-');
  printf("Digite o código da conta de origem: ");
  scanf(" %d", &origem);

  if(!verificarCod(origem, cont, contas)) {
    printf("Código de conta de origem inválido\n");
    return;
  }

  printf("Digite o código da conta de destino: ");
  scanf(" %d", &destino);

  if(!verificarCod(destino, cont, contas)) {
    printf("Código de conta de destino inválido\n");
    return;
  }

  printf("Digite o valor de transferência: ");
  scanf(" %f", &value);

  for(int i = 0; i < cont; i++){
    if(contas[i].numero_conta == origem){
      if(contas[i].saldo_bancario < value){
        printf("Você excedeu o valor que tem em caixa!\n");
        return;
      }
      contas[i].saldo_bancario-= value;
    }else if(contas[i].numero_conta == destino) {
      contas[i].saldo_bancario+= value;
    }
  }
    
  criarTransacao("Houve uma transferência!");
  
  printf("Transferência efetuada com sucesso!\n");
  printLinha('-');
}

void registroGeral() {
  printLinha('-');
  printf("MOVIMENTO GERAL\n");
  for(int i = 0; i < contTransac; i++) {
    printf(" %s\n", transacoes[i]);
  }
  printLinha('-');
}

void relatorios(int cont, Conta *contas) {
  printLinha('-');
  Conta aux;
  for(int i = 0; i < cont; i++) {
    for(int y = i + 1; y < cont; y++){
      if(contas[i].saldo_bancario < contas[y].saldo_bancario){
        aux = contas[i];
        contas[i] = contas[y];
        contas[y] = aux;
      }
    }
    printf("Conta: %d | Nome: %s | Saldo: %.2f\n", contas[i].numero_conta, contas[i].nome_titular, contas[i].saldo_bancario);
  }
  printLinha('-');
}

int main() {
  srand(time(NULL));
  Conta contas[999], auxConta;
  int opcao;
  int cont = 0;

  while(1) {
    chamarMenu();
    printf("Digite a opção que deseja executar: ");
    scanf("%d", &opcao);

    switch(opcao) {
      case 1:
          criarConta(cont, &contas[cont], contas);
          cont++;
          // system("echo clique Enter...");
          // system("read b");
        break;
      case 2:
          deposito(cont, contas);
        break;
      case 3:
          saque(cont, contas);
        break;
      case 4:
          transferencia(cont, contas);
        break;
      case 5:
          registroGeral();
        break;
      case 6:
          relatorios(cont, contas);
        break;
      default:
          printf("\nDigite um valor valido.\n");
        break;

    }
  }

  return 0;
}