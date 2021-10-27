#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define FALSE 0
#define TRUE 1
#define N 1000

struct tEndereco{
	char rua[50];
	char estado[10];
	char CEP[10];
};

struct tPessoa{
	int id;
	int vacina;
	char nome[50];
	char sexo[12];
	char email[70];
	double altura;
	struct tEndereco endereco;
};

int menuPrincipal (void);
int validarEmail (char email[]);
void toupperCase(char str[]);
void removerPulaLinha(char str[]);
int validarSexo(char sexo[]);
int validarAltura(double altura);
int isRepeated (struct tPessoa pessoa[], int ind, int chave);
int pesquisaBinaria (struct tPessoa pessoa[], int chave, int low, int high);
void excluirUsuario (int ind, int chave,int pos ,struct tPessoa pessoa[]);
int pesquisarEmail (int ind, struct tPessoa pessoa[], char chave[]);
void backup (int ind, int chave, struct tPessoa pessoa[], struct tPessoa pessoaBP[]);
void restaurarDados (int ind, int chave, struct tPessoa pessoa[], struct tPessoa pessoaBP[]);

int main (){
	int vacina[N], op, ind = 0, i, k, j, pos, chave, flagBP = 0, indBP;
	char chaveStr[70];
	char resp;
	double aux6;
	struct tPessoa pessoa[N];
	struct tPessoa pessoaAux;
	struct tPessoa pessoaBP[N];
	struct tPessoa aux;
	
srand(time(NULL));
	do{
    	op = menuPrincipal();
	  	switch(op){
			case 1:
			if(ind < N){
				printf ("----- Cadastrar um novo usuario -----\n");
				printf ("Digite o nome completo do usuario: \n");
				setbuf (stdin, NULL);
				fgets (pessoa[ind].nome,50,stdin);
				//********************************EMAIL*****************************************************************
				do{
					printf ("Digite o email do usuario: \n");
					setbuf (stdin, NULL);
					fgets (pessoaAux.email,70,stdin);
				}while(validarEmail(pessoaAux.email)==0);
				//********************************ENDEREÇO*****************************************************************
				printf ("Digite o a sigla do estado do usuario: \n");
				setbuf (stdin, NULL);
				fgets (pessoa[ind].endereco.estado,10,stdin);
				printf ("Digite o a rua do usuario: \n");
				setbuf (stdin, NULL);
				fgets (pessoa[ind].endereco.rua,50,stdin);
				printf ("Digite o a CEP do usuario: \n");
				setbuf (stdin, NULL);
				fgets (pessoa[ind].endereco.CEP,10,stdin);
				//********************************SEXO*****************************************************************
				do{
		    		printf ("Digite o sexo do usuario (entre: \"Masculino\", \"Feminino\" e \"Nao declarar\"): \n");
					setbuf (stdin, NULL);
					fgets (pessoaAux.sexo,14,stdin);
					toupperCase(pessoaAux.sexo);
					removerPulaLinha(pessoaAux.sexo);
				}while(validarSexo(pessoaAux.sexo) == 0);
				//********************************ALTURA*****************************************************************
				do{
					printf("Digite a altura: ");
					scanf("%lf", &pessoaAux.altura);
				}while(validarAltura(pessoaAux.altura) == 0);
				//********************************VACINA*****************************************************************
				do{
					printf("Digite \"S\" caso o usuario foi vacinado,caso contrario digite \"N\": ");
					setbuf (stdin, NULL);
					resp = getchar();
					resp = toupper(resp);
				}while(resp != 'S' && resp != 'N');
				//********************************ID*****************************************************************
				do{
					pessoaAux.id = rand()%9999;
				}while(isRepeated(pessoa, ind, pessoaAux.id) == 1);
				printf("Seu ID e: %d\n", pessoaAux.id);			
				//********************************CRIAR PESSOA {STRING}*****************************************************************
				strcpy(pessoa[ind].sexo, pessoaAux.sexo);
				strcpy(pessoa[ind].email, pessoaAux.email);
				//********************************CRIAR PESSOA*****************************************************************
				pessoa[ind].altura = pessoaAux.altura;
				pessoa[ind].id = pessoaAux.id;
				if(resp == 'S')
					pessoa[ind].vacina = TRUE;
				else
					pessoa[ind].vacina = FALSE;
				ind++;				
				//*************************************BUBBLE SORT*********************************************************
				for(k=1; k<ind; k++){
					for(j=0; j<ind-1; j++){
						if (pessoa[j].id > pessoa[j+1].id){
							aux = pessoa[j];
							pessoa[j] = pessoa[j+1];
							pessoa[j+1] = aux;
							}
						}
					}				
			}else
						printf("MEMORIA CHEIA! EXCLUA UM USUARIO PARA CONTINUAR!\n");
				break;
			case 2:
				printf("----- Editar um Usuario -----\n");
				printf("DIGITE O ID DO USUARIO QUE VAI SER EDITADO: ");
				scanf("%i", &chave);
                pos = pesquisaBinaria(pessoa, chave, 0, ind);
				if (pos != -1){
					printf ("Digite o nome completo do usuario: \n");
				    setbuf (stdin, NULL);
				    fgets (pessoa[pos].nome,50,stdin);

				do{
					printf ("Digite o novo email do usuario: \n");
					setbuf (stdin, NULL);
					fgets (pessoa[pos].email,70,stdin);
				}while(validarEmail(pessoa[pos].email)==0);

				do{
		    		printf ("Digite o sexo atualizado do usuario (entre: \"Masculino\", \"Feminino\" e \"Nao declarar\"): \n");
					setbuf (stdin, NULL);
					fgets (pessoa[pos].sexo,14,stdin);
					toupperCase(pessoa[pos].sexo);
					removerPulaLinha(pessoa[pos].sexo);
				}while(validarSexo(pessoa[pos].sexo) == 0);

				printf ("Digite o a sigla do estado do usuario: \n");
				setbuf (stdin, NULL);
				fgets (pessoa[pos].endereco.estado,10,stdin);
				printf ("Digite o a rua do usuario: \n");
				setbuf (stdin, NULL);
				fgets (pessoa[pos].endereco.rua,50,stdin);
				printf ("Digite o a CEP do usuario: \n");
				setbuf (stdin, NULL);
				fgets (pessoa[pos].endereco.CEP,10,stdin);

					do{
					printf("Digite a altura atualizada: ");
					scanf("%lf", &pessoaAux.altura);
				}while(validarAltura(pessoaAux.altura) == 0);

				do{
					printf("Digite \"S\" \"N\" em relacao a situacao de vacinacao do usuario: ");
					setbuf (stdin, NULL);
					resp = getchar();
					resp = toupper(resp);
				}while(resp != 'S' && resp != 'N');

                if(resp == 'S')
					vacina[pos] = TRUE;
				else
					vacina[pos] = FALSE;
				} else
					printf("\nID NAO ENCONTRADO\n!");				
			
				break;
			case 3:
				printf("----- Excluir um Usuario pelo ID -----\n");
				printf("DIGITE O ID DO USUARIO QUE VAI SER EXCLUIDO: ");
				scanf("%i", &chave);
				pos = pesquisaBinaria(pessoa, chave, 0, ind);
				if (pos != -1){
					excluirUsuario(ind, chave, pos, pessoa);
					ind--;
				} else
					printf("ID NAO ENCONTRADO\n!");
				break;				
				break;
			case 4:
				printf("----- Buscar Usuario por ID -----\n");
				printf("DIGITE O ID DO USUARIO QUE VAI SER FEITA A PESQUISA: ");
				scanf("%i", &chave);
				pos = pesquisaBinaria(pessoa, chave, 0, ind);
				if (pos != -1){
					printf("id: %i\n", pessoa[pos].id);
					printf("Nome: %s", pessoa[pos].nome);
					printf("Email: %s", pessoa[pos].email);
					printf("Sexo: %s \n", pessoa[pos].sexo);
					printf("Estado: %s", pessoa[pos].endereco.estado);
					printf("Rua: %s", pessoa[pos].endereco.rua);
					printf("CEP: %s", pessoa[pos].endereco.CEP);
					printf("Altura: %.2f\n", pessoa[pos].altura);
					if(vacina[pos] == TRUE)
						printf("Situcao: Vacinado\n");
					else
						printf("Situacao: Nao Vacinado\n");
				} else
					printf("ID NAO ENCONTRADO\n!");			
				break;
			case 5:
				printf("----- Pesquisar Usuario pelo Email -----\n");
				printf("digite o email do usuario: ");
				setbuf (stdin, NULL);
				fgets (chaveStr, 70, stdin);
				pos = pesquisarEmail(ind, pessoa, chaveStr);
				if (pos != -1){
					printf("id: %i\n", pessoa[pos].id);
					printf("Nome: %s", pessoa[pos].nome);
					printf("Email: %s", pessoa[pos].email);
					printf("Sexo: %s \n", pessoa[pos].sexo);
					printf("CEP: %s", pessoa[pos].endereco.CEP);
					printf("Estado: %s", pessoa[pos].endereco.estado);
					printf("Rua: %s", pessoa[pos].endereco.rua);
					printf("Altura: %.2f\n", pessoa[pos].altura);
					if(vacina[pos] == TRUE)
						printf("Situcao: Vacinado\n");
					else
						printf("Situacao: Nao Vacinado\n");
				} else
					printf("EMAIL NAO ENCONTRADO\n!");
				break;
			case 6:
				system("cls");
				printf("----- Imprimir um Usuario -----\n");
				for(i = 0; i<ind; i++){
					printf("id: %i\n", pessoa[i].id);
					printf("Nome: %s", pessoa[i].nome);
					printf("Email: %s", pessoa[i].email);
					printf("Sexo: %s \n", pessoa[i].sexo);
					printf("Estado: %s",pessoa[i].endereco.estado);
					printf("Rua: %s",pessoa[i].endereco.rua);
					printf("CEP: %s",pessoa[i].endereco.CEP);
					printf("Altura: %.2f\n", pessoa[i].altura);
					if(vacina[i] == TRUE)
						printf("Situcao: Vacinado\n");
					else
						printf("Situacao: Nao Vacinado\n");
					printf("---------------------------------------------------------\n");
				}
				break;
			case 7:
				printf("----- Fazer um Backup -----\n");
				indBP = ind;
				backup(ind, chave, pessoa, pessoaBP);
				flagBP = 1;				
				break;
			case 8:
			printf("----- Restaurar Dados -----\n");
			if(flagBP == 1){
			restaurarDados(indBP, chave, pessoa, pessoaBP);
			ind = indBP;
			printf("BACKUP FEITO COM SUCESSO\n");
			}else
				printf("UM BACKUP E NECESSARIO PARA A RESTAURACAO DE DADOS!\n");
		}	
}while(op != 0);
	
	
	return 0;
}

int menuPrincipal (void){
  int opc;

  printf ("--------- MENU PRINCIPAL ---------\n\n");
  printf ("1- Cadastrar um novo usuario\n");
  printf ("2- Editar um usuario\n");
  printf ("3- Excluir um usuario\n");
  printf ("4- Buscar um usuario pelo ID\n");
  printf ("5- Buscar um usuario pelo email\n");
  printf ("6- Imprimir todos os usuarios\n");
  printf ("7- Fazer backup de um usuario cadastrado\n");
  printf ("8- Restaurar dados\n");
  printf ("0- Sair\n");
  printf("Digite o numero correspondente da opcao desejada: ");
	scanf("%d",&opc);
	printf("\n");
	return opc;
}

int validarEmail (char email[]){
	int i;
	int	flag=0;

	for(i=0; email[i] != '\0'; i++)
		if(email[i] == '@')
			flag = 1;

	if (flag == 1)
		return 1;
	else
		return 0;
}

void toupperCase(char str[]){
	int i;

	for(i=0; str[i] != '\0'; i++)
		str[i] = toupper(str[i]);

}

void removerPulaLinha(char str[]){
	str[strlen(str)-1] = '\0';
}

int validarSexo(char sexo[]){

	if (strcmp(sexo,"MASCULINO") == 0)
		return 1;
	if(strcmp(sexo,"FEMININO") == 0)
		return 1;
	if (strcmp(sexo,"NAO DECLARAR") == 0)
		return 1;

	return 0;
}

int validarAltura(double altura){
	if(altura >= 1.0 && altura <= 2.0)
		return 1;

	return 0;
}

int isRepeated (struct tPessoa pessoa[], int ind, int chave){
	int i;
	
	for(i=0; i<ind; i++){
		if(chave < pessoa[i].id)
			return 0;
		if(chave == pessoa[i].id)
			return 1;

	}
	return 0;
}

int pesquisaBinaria (struct tPessoa pessoa[], int chave, int low, int high){
	int mid;

	if (low > high)
		return -1;
	else{
		mid = (low+high)/2;
		if (chave == pessoa[mid].id)
			return mid;
		else if (chave>pessoa[mid].id)
			return pesquisaBinaria(pessoa, chave, mid+1, high);
		else
			return pesquisaBinaria(pessoa, chave, low, mid-1);
	}
}

void excluirUsuario (int ind, int chave, int pos, struct tPessoa pessoa[]){
	int i;
	for(i=pos; i<(ind-1); i++){
		pessoa[i] = pessoa[i+1];
	}
}

int pesquisarEmail (int ind, struct tPessoa pessoa[], char chave[]){
	int i;
	
	for(i=0; i<ind; i++)
		if(strcmp(pessoa[i].email, chave) == 0)
			return i;
	return -1;	
}

void backup (int ind, int chave, struct tPessoa pessoa[], struct tPessoa pessoaBP[]){
	int i;
	for(i=0; i<ind; i++){
		pessoaBP[i] = pessoa[i];
	}
}

void restaurarDados (int ind, int chave, struct tPessoa pessoa[], struct tPessoa pessoaBP[]){
	int i;
	for(i=0; i<ind; i++){
		pessoa[i] = pessoaBP[i];
	}
}
