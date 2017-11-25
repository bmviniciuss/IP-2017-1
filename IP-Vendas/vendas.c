/*
/*	Exercícios de Arquivo
/*	Alunos: 
/*		- Vinicius Barbosa de Medeiros
/*		- Jorge Gomes de Melo Júnior
/*	Cadeira: Introdução a Programação 2017.1
/*	Intruções para uso no WINDOWS
/*  Comente linha(s) -> 32.
/*	Descomente linha(s) -> 33, 70, 173.
/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

// -> struct
struct venda {
	int codVendedor;
	char nomeVendedor[151];
	int mesVendas;
	double valorVendas;	
}Venda; // sruct GLOBAL

const char *filename = "vendas.txt";
const char *copy = "copiavendas.txt";

// limpa tela
void clear( void ){
	system("clear"); // uso exclusivo no LINUX
	// system("cls"); // uso exclusivo no WINDOWS
}

// menu
void menu( void ); //exibe menu
int getOpcao( void ); // recebe opção

// math
double media(double valor, int n); // calcula media

// gerencia arquivo
int criaArquivo( void ); // cria arquivo
int verificaArquivo(const char *nome); // verifica se arquivo existe

// insere dados no arquivo
int insereDados( void ); // insere dados no arquivo

// gerencia codigo e mes
int getValores(int *cod, int *mes); // recebe codigo e mes
int hasData(int cod, int mes); // verifica se existe dado com os valores indicado
int removeData(int cod, int mes); // remove dado do arquivo casa exista

// gerencia valores
int getValor(double *mesTotal); // recebe valor a ser modificado no arquivo
int alterarData(int cod, int mes, double valor); // altera o dado no arquivo

// gerencia opções com mes
int getMes(int *mes); // recebe mes
int hasMes(int mes); // verifica se existe ocorrencia do mes no arquivo
int exibaMes(int mes); // exibe ocorrencias com o mes dado

// gerencia opções com codigo
int getCod(int *cod); // recebe codigo
int hasCod(int cod); // verifica ocorrencia do codigo no arquivo
int exibaCod(int cod); // exibe ocorrencias com o codigo dado

int main(){
	// setlocale(LC_ALL, "Portuguese"); // Uso exclusivo no WINDOWS
	int on = 1;
	int opcao;
	int cod = 0, mes = 0;
	char op;
	double mesTotal;

	while(on){
		menu();
		opcao = getOpcao();

		// cria arquivo
		if(opcao == 1){
			if(verificaArquivo(filename)){
				printf("\nCRIAR ARQUIVO!\n");
				printf("Caso o arquivo já exista. TODOS os dados seram perdidos.\n");
				printf("Digite sim se você quer fazer isso: (s/n) ");
				while(1){
					scanf("%c", &op);
					if(op == 's' || op == 'S'){
						criaArquivo();
						clear();
						break;
					}
					else if(op == 'n' || op == 'N'){
						break;
					}
				}
			}
			else{
				criaArquivo();
			}
		}
		// insere registro no arquivo
		else if(opcao == 2){
			clear();
			printf("O Programa pedirar a informação de cada registro.\n");
			printf("Para parar bote o codigo do vendedor igual a 0(zero).\n");
			printf("Aperte ENTER para começar.\n");
			getchar();
			getchar();
			insereDados();
		}
		// exlui registro, dado cod do vendedor e mes, se houver
		else if(opcao == 3){
			if(getValores(&cod, &mes)){
				// printf("COD: %d - MES: %d\n", cod, mes);
				// printf("HAS DATA: %d\n", hasData(cod, mes));
				if(!hasData(cod, mes)){
					removeData(cod, mes);
				}
				else{
					printf("Não existe esse registro nesse arquivo.\n\n");
				}
			}
		} 
		// dado um codigo e mes, alterar o valor da venda no arquivo, se houver
		else if(opcao == 4){
			if(getValores(&cod, &mes)){
				if(!hasData(cod, mes)){
					getValor(&mesTotal);
					alterarData(cod, mes, mesTotal);
				}
				else{
					printf("Não existe esse registro nesse arquivo.\n\n");
				}
			}
		}
		// dado o mes imprimir o valor total de vendas, 
		else if(opcao == 5){
			if(!getMes(&mes)){
				if(!hasMes(mes)){
					exibaMes(mes);
				}
				else{
					printf("Não existe nenhum resgistro do mes %d no arquivo\n\n", mes);
				}

			}
		}
		// dado um cod, listar todas os registros e valor medio
		else if(opcao == 6){
			clear();
			if(getCod(&cod)){
				if(!hasCod(cod)){
					exibaCod(cod);
				}
				else{
					printf("Não existe esse codigo no registro. Tente novamente\n\n");
				}
			}
		}
		else if(opcao == 7){
			printf("Saindo...\n");
			on = 0;
			break;
		}
		else{
			printf("O Arquivo não foi criado. Tente realizar a opção 1.\n");
		}

	}

	// system("pause"); // uso exclusivo no WINDOWS
	return 0;
}

void menu( void ){
	printf("Menu: \n");
	printf("1 - Criar arquivo de dados\n");
	printf("2 - Incluir registros no arquivo\n");
	printf("3 - Remover registro\n");
	printf("4 - Modificar registro\n");
	printf("5 - Registros do mes\n");
	printf("6 - Registros do vendedor\n");
	printf("7 - Sair\n");
}

int getOpcao( void ){
	int op;
	while(1){
		printf("Qual opção você deseja: ");
		scanf("%d", &op);
		if(op >= 1 && op <= 7){
			return op;
			break;
		}
		else{
			printf("Esse valor não é válido. Tente novamente.\n");
		}
	}
}

int criaArquivo( void ){
	FILE *arquivo;

	arquivo = fopen(filename, "w");

	if(!arquivo){
		printf("Não foi possível abrir esse arquivo.\n");
		return 1;
	}
	else{
		fclose(arquivo);
		return 0;
	}
}

int verificaArquivo(const char *nome){
	int n = 0;
	char c;
	FILE *arquivo;

	arquivo = fopen(nome, "a+");

	if(!arquivo){
		return 0;
	}
	else{
		return 1;
	}
	fclose(arquivo);
}

int insereDados( void ){
	int i = 1;
	FILE *arquivo;

	arquivo = fopen(filename, "a");

	if(!arquivo){
		printf("Não foi possível abrir esse arquivo. Tente novamente\n");
		return 1;
	}
	else{
		while(1){
			printf("Digite o Código do vendedor %d (0 para parar): ", i);
			scanf("%d", &Venda.codVendedor);

			if(Venda.codVendedor == 0){
				break;
			}

			printf("Digite o nome do vendedor %d: ", i);
			scanf("%s", Venda.nomeVendedor);

			while(1){
				printf("Mês de Vendas(1-12): ");
				scanf("%d", &Venda.mesVendas);

				if(Venda.mesVendas >= 1 && Venda.mesVendas <= 12){
					break;
				}
				else{
					printf("Esse valor não é válido. Tente novamente\n");
				}
			}

			while(1){
				printf("Valor total de vendas do mes %d do vendedor %d: ", Venda.mesVendas, i);
				scanf("%lf", &Venda.valorVendas);
				if(Venda.valorVendas >= 0){
					break;
				}
				else{
					printf("Esse valor não é válido. Tente novamente.\n");
				}

			}

			fprintf(arquivo, "%d %s %d %.2lf\n", 
				Venda.codVendedor,
				Venda.nomeVendedor,
				Venda.mesVendas,
				Venda.valorVendas
				);

			printf("\n");
			i++;
		}
	}

	fclose(arquivo);
	return 0;	
}

int hasData(int cod, int mes){
	FILE *arquivo;
	arquivo = fopen(filename, "r");

	if(!arquivo){
		printf("Não foi possível abrir o arquivo.\n");
		return 1;
	}
	else{
		while((fscanf(arquivo, "%d %s %d %lf",
			&Venda.codVendedor,
			Venda.nomeVendedor,
			&Venda.mesVendas,
			&Venda.valorVendas)) != EOF){
				if(Venda.codVendedor == cod && Venda.mesVendas == mes){
					return 0;
				}
		}
	}

	fclose(arquivo);
	return 1;
}

int getValores(int *cod, int *mes){
	int localCod, localMes;

	printf("Codigo a ser usado(0 - cancela operação): ");
	scanf("%d", &localCod);

	if(localCod == 0){
		return 0;
	}
	else{
		while(1){
			printf("Mês a ser usado: ");
			scanf("%d", &localMes);

			if(localMes >= 1 && localMes <= 12){
				*cod = localCod;
				*mes = localMes;
				break;
			}
			else{
				printf("Esse mes não é válido. Tente novamente.\n");
			}
		}
	}

	return 1;
}

int removeData(int cod, int mes){
	FILE *arquivo, *copia;
	arquivo = fopen(filename, "r");
	copia = fopen(copy, "w");

	if(!arquivo || !copia){
		printf("Não foi possível abrir o arquivo.\n");
		return 1;
	}
	else{
		while((fscanf(arquivo, "%d %s %d %lf",
			&Venda.codVendedor,
			Venda.nomeVendedor,
			&Venda.mesVendas,
			&Venda.valorVendas)) != EOF){
			// printf("VENDA COD: %d - VENDA MES: %d\n", Venda.codVendedor, Venda.mesVendas);
			// printf("COD: %d - MES: %d\n", cod, mes);
			if((Venda.codVendedor == cod) && (Venda.mesVendas == mes)){}
			else{
				// printf("DENTRO\n");
				fprintf(copia, "%d %s %d %.2lf\n", 
							Venda.codVendedor,
							Venda.nomeVendedor,
							Venda.mesVendas,
							Venda.valorVendas
							);
			}
		}
	}

	remove(filename);
	rename(copy, filename);
	fclose(arquivo);
	fclose(copia);

	return 0;
}

int getValor(double *mesTotal){
	double localValor;
	while(1){
		printf("Digite o valor total de vendas a ser modificado: ");
		scanf("%lf", &localValor);

		if(localValor >= 0){
			*mesTotal = localValor;
			break;
		}
		else{
			printf("Esse valor não é válido. Tente novamente.\n");
		}
	}
	return 0;
}

int alterarData(int cod, int mes, double valor){
	FILE *arquivo, *copia;
	arquivo = fopen(filename, "r");
	copia = fopen(copy, "w");

	if(!arquivo || !copia){
		printf("Não foi possível abrir o arquivo.\n");
		return 1;
	}
	else{
		while((fscanf(arquivo, "%d %s %d %lf",
			&Venda.codVendedor,
			Venda.nomeVendedor,
			&Venda.mesVendas,
			&Venda.valorVendas)) != EOF){
			// printf("VENDA COD: %d - VENDA MES: %d\n", Venda.codVendedor, Venda.mesVendas);
			// printf("COD: %d - MES: %d\n", cod, mes);
			if((Venda.codVendedor == cod) && (Venda.mesVendas == mes)){
				fprintf(copia, "%d %s %d %.2lf\n", 
							Venda.codVendedor,
							Venda.nomeVendedor,
							Venda.mesVendas,
							valor
							);
			}
			else{
				// printf("DENTRO\n");
				fprintf(copia, "%d %s %d %.2lf\n", 
							Venda.codVendedor,
							Venda.nomeVendedor,
							Venda.mesVendas,
							Venda.valorVendas
							);
			}
		}
	}

	remove(filename);
	rename(copy, filename);
	fclose(arquivo);
	fclose(copia);

	return 0;
}

int getMes(int *mes){
	int localMes;
	while(1){
		printf("Mês a ser exibido: ");
		scanf("%d", &localMes);

		if(localMes >=1 && localMes <= 12){
			*mes = localMes;
			break;
		}
		else{
			printf("Esse valor não é válido. Tente novamente.\n");
		}
	}
	return 0;
}

int hasMes(int mes){
	FILE *arquivo;
	arquivo = fopen(filename, "r");

	if(!arquivo){
		printf("Não foi possível abrir o arquivo.\n");
		return 1;
	}
	else{
		while((fscanf(arquivo, "%d %s %d %lf",
			&Venda.codVendedor,
			Venda.nomeVendedor,
			&Venda.mesVendas,
			&Venda.valorVendas)) != EOF){
				if(Venda.mesVendas == mes){
					return 0;
				}
		}
	}

	fclose(arquivo);
	return 1;
}

double media(double valor, int n){
	return (double)(valor/n);
}

int exibaMes(int mes){
	int n = 0;
	double totalMes = 0;
	double mediaMes = 0;
	FILE *arquivo;

	arquivo = fopen(filename, "r");
	if(!arquivo){
		printf("Não foi possível abrir esse arquivo\n");
		return 1;
	}
	else{
		printf("------------------------------------\n");
		printf("%5s%9s%8s%12s\n", "cod.", "nome", "mes", "vendas");
		printf("------------------------------------\n");
		while((fscanf(arquivo, "%d %s %d %lf",
			&Venda.codVendedor,
			Venda.nomeVendedor,
			&Venda.mesVendas,
			&Venda.valorVendas)) != EOF){
				if(Venda.mesVendas == mes){
					n++;
					totalMes += Venda.valorVendas;
					// printf(" cod.     nome     mes     vendas\n");
					// printf("  1     vinicius    1      10000.00\n");
					printf("%3d%13s%5d%14.2lf\n",
						Venda.codVendedor,
						Venda.nomeVendedor,
						Venda.mesVendas,
						Venda.valorVendas);
				}

		}
		printf("------------------------------------\n");
		// printf("MEDIA DE VENDAS DO MES:   1000000.00\n");
		// printf("TOTAL:                          .00\n");
		printf("%6s%29.2lf\n", "TOTAL:", totalMes);
		mediaMes = media(totalMes, n);
		printf("%23s%12.2lf\n", "MEDIA DE VENDAS DO MES:", mediaMes);
	}

	fclose(arquivo);
	return 0;
}


int getCod(int *cod){
	int localCod;

	printf("Codigo a ser usado(0 - cancela operação): ");
	scanf("%d", &localCod);

	if(localCod == 0){
		return 0;
	}
	*cod = localCod;
	return 1;
}

int hasCod(int cod){
	FILE *arquivo;
	arquivo = fopen(filename, "r");

	if(!arquivo){
		printf("Não foi possível abrir o arquivo.\n");
		return 1;
	}
	else{
		while((fscanf(arquivo, "%d %s %d %lf",
			&Venda.codVendedor,
			Venda.nomeVendedor,
			&Venda.mesVendas,
			&Venda.valorVendas)) != EOF){
				if(Venda.codVendedor == cod){
					return 0;
				}
		}
	}

	fclose(arquivo);
	return 1;
}

int exibaCod(int cod){
	int n = 0;
	double totalMes = 0;
	double mediaMes = 0;
	FILE *arquivo;

	arquivo = fopen(filename, "r");
	if(!arquivo){
		printf("Não foi possível abrir esse arquivo\n");
		return 1;
	}
	else{
		printf("------------------------------------\n");
		printf("%5s%9s%8s%12s\n", "cod.", "nome", "mes", "vendas");
		printf("------------------------------------\n");
		while((fscanf(arquivo, "%d %s %d %lf",
			&Venda.codVendedor,
			Venda.nomeVendedor,
			&Venda.mesVendas,
			&Venda.valorVendas)) != EOF){
				if(Venda.codVendedor == cod){
					n++;
					totalMes += Venda.valorVendas;
					printf("%3d%13s%5d%14.2lf\n",
						Venda.codVendedor,
						Venda.nomeVendedor,
						Venda.mesVendas,
						Venda.valorVendas);
				}

		}
		printf("------------------------------------\n");
		printf("%6s%29.2lf\n", "TOTAL:", totalMes);
		mediaMes = media(totalMes, n);
		printf("%25s%10.2lf\n\n", "MEDIA VENDAS DO VENDEDOR: ", mediaMes);
	}

	fclose(arquivo);
	return 0;
}
