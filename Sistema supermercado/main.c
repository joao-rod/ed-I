#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int dia;
	int mes;
	int ano;
}Data;

typedef struct{
	char name[200];
	float value;
	int codBarra;
	int estoque;
	Data validade;
}Produto;

typedef struct{
	int contProdutos;
	float totalVendas;
}Venda;


int main() {
	Produto produtos[999];
	Venda vendas;
	int cont = 0, opc, aux[999];
	vendas.contProdutos = 0;
	vendas.totalVendas = 0;

	while (1) {
		// Menu
		printf("*=====================Menu======================*\n");
		printf("*\t1 -----\tCadastrar novo produto\t\t*\n");
		printf("*\t2 -----\tListar produtos cadastrados\t*\n");
		printf("*\t3 -----\tRealizar uma venda\t\t*\n");
		printf("*\t4 -----\tAcompanhar operações de vendas\t*\n");
		printf("*\t5 -----\tFinalizar aplicação\t\t*\n");
		printf("*===============================================*\n");
		printf("\nDigite a opção desejada: ");
		scanf("%d", &opc);
		system("clear");

		if (opc == 1) { // Cadastro de novos produtos
			int cod, validateCod = 0;

			printf("Digite o codigo de barras: ");
			scanf(" %d", &cod);
			
			// Validação de existência de código de barras
			for (int i = 0; i < cont; i++)
				if (cod == produtos[i].codBarra)
					validateCod = 1;

			if (validateCod){
				printf("Já exite um código de barras com este valor!!\n");
				system("echo Clique Enter para voltar ao Menu...");
				system("read b");
			} else {
				produtos[cont].codBarra = cod;
				printf("Digite o nome do produto: ");
				scanf(" %[^\n]s", produtos[cont].name);
				printf("Digite o valor: R$ ");
				scanf(" %f", &produtos[cont].value);
				printf("Digite a validade: ");
				scanf("%d/%d/%d", &produtos[cont].validade.dia, &produtos[cont].validade.mes, &produtos[cont].validade.ano);
				printf("Digite a quantidade desse produto: ");
				scanf(" %d", &produtos[cont].estoque);
				aux[cont] = produtos[cont].estoque;
				system("clear");
				system("echo Produto cadastrado com sucesso!!Clique Enter para voltar ao Menu...");
				system("read b");
				cont++;
			}
			system("clear");
			
		} else if (opc == 2){ // Listagem dos produtos cadastrados
			for (int i= 0; i < cont; i++){
				printf("Codigo de barras:\t%d\n", produtos[i].codBarra);
				printf("Nome do produto:\t%s\n", produtos[i].name);
				printf("Valor do produto:\tR$ %.2f\n", produtos[i].value);
				printf("Data de validade:\t%02d/%02d/%d\n", produtos[i].validade.dia, produtos[i].validade.mes, produtos[i].validade.ano);
				printf("Quantia em estoque:\t%02d\n\n", produtos[i].estoque);
			}
			system("echo Clique Enter para voltar ao Menu...");
			system("read b");
			system("clear");

		} else if (opc == 3){ // Operações de vendas
			int cod, stop = 1, qntProdutos;
			char compra;
			while (stop){
				int codNotFound = 1;
				printf("Digite o codigo de barras: ");
				scanf("%d", &cod);
				system("clear");
				for (int i= 0; i < cont; i++){
					if (cod == produtos[i].codBarra){
						// Mostra os detalhes do produto
						printf("Codigo de barras:\t%d\n", produtos[i].codBarra);
						printf("Nome do produto:\t%s\n", produtos[i].name);
						printf("Valor do produto:\tR$ %.2f\n", produtos[i].value);
						printf("Data de validade:\t%02d/%02d/%d\n", produtos[i].validade.dia, produtos[i].validade.mes, produtos[i].validade.ano);
						printf("Quantia em estoque:\t%02d\n\n", produtos[i].estoque);

						codNotFound = 0;

						// Operação de vendas
						printf("Deseja confirmar a venda [s/n]: ");
						scanf(" %c", &compra);
						if (compra == 's'){
							if (produtos[i].estoque > 0) {
								printf("Quantos produtos: ");
								scanf(" %d", &qntProdutos);
								if (qntProdutos <= produtos[i].estoque){
									vendas.totalVendas += qntProdutos * produtos[i].value;
									produtos[i].estoque -= qntProdutos;
									vendas.contProdutos += qntProdutos;
									printf("\nVenda bem sucedida!!\n\n");
								} else {
									system("echo Quantidade insuficiente em estoque...");
									system("read b");
								}
							} else{
								system("echo Produto em falta no estoque!!"); 
								system("read b");
							}

						} else {
							stop = 0;
							break;
						} 
						printf("Realizar outra venda [s/n]: ");
						scanf(" %c", &compra);
						(compra == 's') ? stop : stop--;
						
						break;
					} else
						codNotFound = 1;
				}
				if (codNotFound){
					system("echo Produto com este codigo não encontarado. Clique Enter para voltar ao Menu...");
					system("read b");
					stop = 0;
				}
			}
			system("clear");

		} else if (opc == 4){ // Acompanhar vendas
			for (int i = 0; i < cont; i++){
				printf("Produto: %s - %d\t\t", produtos[i].name, produtos[i].codBarra);
				printf("Faturado: R$ %.2f\t\t", produtos[i].value * (aux[i] - produtos[i].estoque));
				printf("Vendido: %d\t\t", aux[i] - produtos[i].estoque);
				printf("Restante: %d\n\n", produtos[i].estoque);
			}
				
			printf("Vendas totais até o momento: %d\n", vendas.contProdutos);
			printf("Fatura total até o momento: R$ %.2f\n\n", vendas.totalVendas);
			system("echo Clique Enter para voltar ao Menu...");
			system("read b");
			system("clear");

		} else if (opc == 5){ // Encerra aplicação
			printf("Caixa fechado em R$ %.2f\n", vendas.totalVendas);
			break;

		} else {
			system("echo Digite uma opção válida...");
			system("read b");
		}
	}

	return 0;
}