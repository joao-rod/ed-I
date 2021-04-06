#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct stat st;

typedef struct{
  int password;
  int status;
}Master;

typedef struct{
  char nome[100];
  int password;
  int cpf;
}Client;

typedef struct{
  char nome[100];
  int cnpj;
  int cod;
  float juros;
}Agency;

typedef struct{
  float valor;
  float total;
  int parcelas;
  int pessoa;
  int banco;
}Emprestimo;

void clickEnter(){
  printf("\nclique ENTER para retornar ao menu...\n");
  setbuf(stdin, NULL);
  getchar();
}

int getMenu(){
  int opc;
  system("clear");
  printf("BEM VINDO AO SISTEMA DE EMPRÉSTIMOS SAFE\n\n");
  printf("Aqui voce pode solicitar seu empréstimo pessoal.\nVocê também pode cunsultar sua situação conosco\n\n");
  printf("1 ------------\tJá sou cliente SAFE\n");
  printf("2 ------------\tMe cadastrar no SAFE\n");
  printf("3 ------------\tAdicionar uma agência ao SAFE\n");
  printf("4 ------------\tListar as agências SAFE\n");
  printf("5 ------------\tFechar aplicação\n\n");
  printf("Digite o número da opção desejada: ");
  scanf(" %d",&opc);

  return opc;
}

int menuClient(){
  int opc;
  system("clear");
  printf("AREA DO CLIENTE\n\n");
  printf("1 ------------\tSolicitar um empréstimo\n");
  printf("2 ------------\tConsultar meus empréstimo\n");
  printf("3 ------------\tFazer Logout\n\n");
  printf("Digite o numero da opção desejada: ");
  scanf(" %d", &opc);

  return opc;
}

void createClient(FILE* clients){
  Client client;
  int cpf, validateUser = 1;
  system("clear");
  printf("Para iniciarmos, digite seu cpf: ");
  scanf(" %d", &cpf);
  fseek(clients, 0, SEEK_SET);
  while(fread(&client, sizeof(Client), 1, clients)){
    if (cpf == client.cpf){
      printf("Voĉe já possui uma conta SAFE.\n");
      clickEnter();
      validateUser = 0;
      break;
    }
  }
  if(validateUser == 1){
    client.cpf = cpf;
    printf("Podemos prosseguir, digite seu nome: ");
    scanf(" %[^\n]s", client.nome);
    printf("Para finalizarmos o seu cadastro, crie uma senha numerica: ");
    scanf(" %d", &client.password);fseek(clients, 0, SEEK_END);

    fseek(clients, 0, SEEK_END);
    int validate = fwrite(&client, sizeof(Client), 1, clients);
    if (!validate)
      printf("Ocorreu um erro inesperado. Tente novamente depois.");
    else {
      printf("Tudo certo por aqui.\nCadastro realizado.\n\nclique ENTER...\n");
    }
  }
}

void addAgency(FILE* agency, int pass){
  Agency agencia;
  int passwd;
  system("clear");
  printf("Precisamos verificar se você é um administrador.\n\nDigite a senha de administrador: ");
  scanf(" %d", &passwd);
  if (passwd == pass){
    printf("Vamos iniciar a adição de uma agência.\nPara isso digite o nome da agência: ");
    scanf(" %[^\n]s", agencia.nome);
    printf("Código de identificação da agência: ");
    scanf(" %d", &agencia.cod);
    printf("Digite a taxa de juros que esta agência aplicará: R$");
    scanf(" %f", &agencia.juros);

    fseek(agency, 0, SEEK_END);
    int validate = fwrite(&agencia, sizeof(Agency), 1, agency);
    if (validate){
      printf("Tudo certo por aqui. Você cadastrou uma nova agência.\n");
      clickEnter();
    } else {
      printf("Algo não saiu bem. Tente de novo...\n");
      clickEnter();
    }
  } else {
    printf("Você não têm privilégios de administrador.\n");
    clickEnter();
  }
}

int approved = 0;
int cpfClient;
int loginClient(FILE* clients){
  system("clear");
  Client client;
  int cpf, password;
  printf("Olá cliente SAFE, para prosseguirmos preecha os dados abaixo para acessar sua conta.\n\n");
  printf("Digite seu CPF: ");
  scanf(" %d", &cpf);

  fseek(clients, 0, SEEK_SET);
  while(fread(&client, sizeof(Client), 1, clients)){
    if (cpf == client.cpf) {
      printf("Agora digite a sua senha: ");
      scanf(" %d", &password);
      if (password == client.password){
        cpfClient = cpf;
        approved = 1;
        break;
      }
      else {
        approved = 2;
        break;
      }

    } else {
      approved = 0;
    }
  }
}

FILE* openFp(char* name){
  FILE* f = fopen(name, "rb+");
  if (!f)
    f = fopen(name, "wb+");
  if (!f)
    printf("Não foi possível abrir o arquivo...");

  return f;
}

int getCodAgency(FILE* agency){
  Agency agencia;
  system("clear");
  printf("Agências cadastradas na SAFE\n\n");
  printf("cod.\tnome\n");
  fseek(agency, 0, SEEK_SET);
  while(fread(&agencia, sizeof(Agency), 1, agency)){
    printf("%d\t%s\n", agencia.cod, agencia.nome);
  }
  int opc;
  printf("\nDigite o código da agência que deseja contratar o emprestimo: ");
  scanf(" %d", &opc);

  return opc;
}

void getAgency(FILE* agency){
  Agency agencia;
  system("clear");
  printf("Agências cadastradas na SAFE\n\n");
  printf("cod.\tnome\n");
  fseek(agency, 0, SEEK_SET);
  while(fread(&agencia, sizeof(Agency), 1, agency)){
    printf("%d\t%s\n", agencia.cod, agencia.nome);
  }
  clickEnter();
}

void requestEmprestimo(FILE* emprestimos, FILE* agency, FILE* clients){
  Emprestimo emprestimo;
  Agency agencia;
  Client client;
  float valor, total;
  int parcelas, password, stopValidate = 0;

  int getBanco = getCodAgency(agency);

  system("clear");
  fseek(agency, 0, SEEK_SET);
  while(fread(&agencia, sizeof(Agency), 1, agency)){
    if (getBanco == agencia.cod){
      printf("Vamos lá\n\n");
      printf("Para começar, digite o valor a ser contratado: ");
      scanf(" %f", &valor);
      total = valor;
      printf("Agora digite em quntas parcelas irá pagar: ");
      scanf(" %d", &parcelas);
      system("clear");
      printf("\nOk\n");
      printf("\nINFORMATIVO\n\n");
      printf("Essa agência fornece empréstimos com juros de %.2f%% ao mes.\n", agencia.juros);
      printf("Você estará pagando um montande de R$%.2f para o valor que escolheu.\n", valor + (valor * (agencia.juros / 100)));
      printf("Os juros serão de R$%.2f ao mes.\n", (valor / parcelas) * (agencia.juros / 100));
      valor /= parcelas;
      valor += valor * (agencia.juros / 100);
      printf("Você pagará %d parcela no valor de R$%.2f cada.\n\n", parcelas, valor);
      printf("Para confirmar contratação digite sua senha ou digite 0 para cancelar: ");
      scanf(" %d", &password);
      printf("\n");
      fseek(clients, 0, SEEK_SET);
      while(fread(&client, sizeof(Client), 1, clients)){
        if (cpfClient == client.cpf && password == client.password){
          emprestimo.pessoa = cpfClient;
          emprestimo.banco = getBanco;
          emprestimo.total = total;
          emprestimo.valor = valor;
          emprestimo.parcelas = parcelas;

          fseek(emprestimos, 0, SEEK_END);
          int validate = fwrite(&emprestimo, sizeof(Emprestimo), 1, emprestimos);
          if (validate){
            printf("Tudo certo por aqui. Você já pode ver os detalhes na opção 2 do menu.\n\n");
            stopValidate = 1;
            break;
          }
          else printf("Algo saiu mal. Tente novamente depois.\n\n");
        } else if(password == 0){
          printf("Ok. A operação foi cancelada!!\n\n");
          stopValidate = 1;
          break;
        } 
      }    
    }
  }
  if (stopValidate == 0)
    printf("Houve um erro na validação. Cheque se os dados inseridos estão corretos\n\n");

  clickEnter();
}

void getEmprestimo(FILE* emprestimos, FILE* agency, FILE* clients){
  Emprestimo emprestimo;
  Client client;
  Agency agencia;
  system("clear");
  fseek(clients, 0, SEEK_SET);
  while(fread(&client, sizeof(Client), 1, clients)){
    if (cpfClient == client.cpf){
      printf("Olá %s,\n\n", client.nome);
      break;
    }
  }
  printf("Abaixo estão listados os seus empréstimos\n\n");
  fseek(emprestimos, 0, SEEK_SET);
  while(fread(&emprestimo, sizeof(Emprestimo), 1, emprestimos)){
    if (cpfClient == emprestimo.pessoa){
      printf("Valor contratado:\t%.2f\n", emprestimo.total);
      printf("Valor da parcela:\t%.2f\n", emprestimo.valor);
      printf("Numero de parcelas:\t%d\n", emprestimo.parcelas);
      int auxCod = emprestimo.banco;
      fseek(agency, 0, SEEK_SET);
      while(fread(&agencia, sizeof(Agency), 1, agency)){
        if(auxCod == agencia.cod){
          printf("Nome da gência:\t\t%s\n\n", agencia.nome);
        }
      }
    }
  }
  clickEnter();
}

void areaClient(FILE* clients, FILE* agency, FILE* emprestimo){
  loginClient(clients);
  if (approved == 1) {
    printf("Area do cliente\n\n");
    int stop = 1;
    while(stop){
      switch(menuClient()){
        case 1:
          requestEmprestimo(emprestimo, agency, clients);
        break;

        case 2:
          getEmprestimo(emprestimo, agency, clients);
        break;

        case 3: 
          stop = 0;
        break;

        default: 
          printf("Entrada inválida.\n");
          clickEnter();
        break;
      }
    }
  } else if (approved == 2){
    system("clear");
    printf("\n\nSenha incorreta. Por favor, se esqueceu sua senha entre em contato com a nossa central.\n\n");
    clickEnter();
  } else {
    system("clear");
    printf("\n\nParece que você não possui uma conta ativa :(\n\n");
    clickEnter();
  }
}

int passAdmin(FILE* master, char name[]){
  Master pass;
  int password;
  // Checando o tamanho do arquivo: se igual a 0, arquivo não tem registros;
  stat(name, &st);
  off_t size = st.st_size;

  while(1){
    if(size == 0){
      printf("Você é um administrador.\n");
      printf("Para cadastrar novas agências você precisa de acesso especial.\n");
      printf("Por isso, defina uma senha: ");
      scanf(" %d", &password);
      if (password > 999){
        pass.password = password;
        fseek(master, 0, SEEK_END);
        fwrite(&pass, sizeof(Master), 1, master);
        break;
      } else printf("\nSua senha deve ter 4 digitos ou mais.\n\n");
    } else {
      fseek(master, 0, SEEK_SET);
      while(fread(&pass, sizeof(Master), 1, master)){
        password = pass.password;
        break;
      }
      printf("Você já é um administrador\n\n");
      break;
    }
  }
  fclose(master);
  clickEnter();

  return password;
}

int main(){
  char name[] = {"master"};

  FILE* pass = openFp(name);
  FILE* clients = openFp("clientes");
  FILE* agency = openFp("agencias");
  FILE* emprestimo = openFp("emprestimos");

  int passwordMaster = passAdmin(pass, name);
  while(1){
    system("clear");
    switch(getMenu()){
      case 1:
        areaClient(clients, agency, emprestimo);
      break;

      case 2:
        createClient(clients);
      break;

      case 3:
        addAgency(agency, passwordMaster);
      break;

      case 4:
        getAgency(agency);
      break;

      case 5: return 0;

      default: 
        system("clear");
        printf("Opção inválida.\n");
        clickEnter();
      break;
    }
  }
  fclose(clients);
  fclose(agency);
  fclose(emprestimo);
}