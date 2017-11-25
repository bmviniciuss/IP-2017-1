/*
Feito por:
- Vinicius Barbosa de Medeiros
- Aldevison Santos Ferreira

## Instruções:
- Para uso no Windows descomente as linhas referentes ao setlocale, e a função clear;
- descomente linhas: 16, 43, 144;
- comente linha: 143;
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <locale.h>

//constante que representa numero de bandas
const int tam = 5;

//Banda Struct
typedef struct{
		char nome[250];
		char genero[250];
		int integrantes;
		int ranking;
	}Banda;

//Funções.
void addBands(Banda *content, int tam);
void showBands(Banda *content, int tam);
void showBandbyID(Banda *content, int tam, int id);
int rankQuery(Banda *content, int tam, int desejado);
int genreQuery(Banda *content, int tam, char *desejado);
int nameQuery(Banda *content, int tam, char *desejado);
int printQuery(Banda *content, int tam, char *desejado);
int printQueryName(Banda *content, int tam, char *desejado);
int options(void);
void clear(void);

//main
int main(){
	// setlocale(LC_ALL, "Portuguese"); //uso no windows
	Banda bandas[tam];
	int an, controle = 1, query, rankDesejado;
	char estiloDesejado[251], nomeDesejado[251];

	addBands(bandas, tam);
	showBands(bandas, tam);

	while(controle){
		an = options();
		getchar(); // limpa \n
	
		switch(an){
			case 1:
				//digitar dados da banda
				addBands(bandas, tam);
				break;
			case 2:
				//listar bandas
				showBands(bandas, tam);
				break;
			case 3:
				//pesquisar pelo ranking
				clear();
				printf("Qual o ranking desejado: ");
				scanf("%d", &rankDesejado);


				query = rankQuery(bandas,tam, rankDesejado);
				
				if(query < 0){
					printf("Não foi encontrado. Tente Novamente\n");
				}
				else{
					showBandbyID(bandas, tam, query);
				}

				break;
			case 4:
				//pesquisar pelo estilo de musica
				clear();
				printf("Qual o estilo desejado: ");
				scanf("%[^\n]s", estiloDesejado);
				getchar(); //limpa \n

				query = genreQuery(bandas, tam, estiloDesejado);

				if(query < 0){
					printf("Não foi encontrado. Tente Novamente\n");
				}
				else{
					clear();
					printf("Banda(s) Pesquisada(s): \n");
					printf("%-15s|%-15s|%-15s|%-15s\n", "Nome", "Genero", "Integrantes", "Ranking");
					printf("-------------------------------------------------------\n");
					printQuery(bandas, tam, estiloDesejado);
					printf("-------------------------------------------------------\n");
					printf("\n");
				}
				break;
			case 5:
				//pesquisar pelo nome da banda
				clear();
				printf("Qual o nome da banda: ");
				scanf("%[^\n]s", nomeDesejado);
				getchar(); //limpa \n

				query = nameQuery(bandas, tam, nomeDesejado);

				if(query < 0){
					printf("Não foi encontrado. Tente Novamente\n");
				}
				else{
					clear();
					printf("%s esta no seus favoritos.\n", nomeDesejado);
					printf("Banda(s) Pesquisada(s): \n");
					printf("%-15s|%-15s|%-15s|%-15s\n", "Nome", "Genero", "Integrantes", "Ranking");
					printf("-------------------------------------------------------\n");
					printQueryName(bandas, tam, nomeDesejado);
					printf("-------------------------------------------------------\n");
					printf("\n");
				}
				break;
			case 6:
				//fim do programa
				printf("saindo...\n");
				controle = 0;
				break;
		}
	}
	
	
	return 0;
}

void clear(void){
	/*
	Limpa a tela. Para uso no windows deve comentar 
	a primeira linha e descomentar a segunda
	*/
	system("clear");
	// system("cls"); //uso no windows
}


void addBands(Banda *content, int tam){
	//Adiciona n(tam) bandas
	int i, integrantes, ranking;
	char nome[250], genero[250];

	for(i = 0; i < tam; i++){
		clear();
		printf("Digite o nome da banda %d: ",i + 1);
		scanf("%[^\n]s", nome);
		getchar(); // limpa \n
		strcpy(content[i].nome, nome);

		printf("Digite o genero da banda %d: ", i + 1);
		scanf("%[^\n]s", genero);
		getchar(); // limpa \n
		strcpy(content[i].genero, genero);

		printf("Digite o numero de integrantes da banda %d: ", i + 1);
		scanf("%d", &integrantes);
		content[i].integrantes = integrantes;

		printf("Digite a posicao da banda %d: ", i + 1);
		scanf("%d", &ranking);
		content[i].ranking = ranking;

		getchar(); // limpa \n

	}
}


void showBands(Banda *content, int tam){
	//mostra todas as bandas de forma tabular
	int i;

	clear();
	printf("Banda(s) Cadastrada(s): \n");
	printf("%-15s|%-15s|%-15s|%-15s\n", "Nome", "Genero", "Integrantes", "Ranking");
	printf("-------------------------------------------------------\n");

	for(i = 0; i < tam; i++){
		printf("%-16s%-16s%-16d%-15d\n", content[i].nome, content[i].genero, content[i].integrantes, content[i].ranking);
	}
	printf("-------------------------------------------------------\n");
	printf("\n");
}


int options(void){
	// mostra opções e pega input do usuario
	int an;

	while(1){
			printf("1 - Digitar dados das bandas\n");
			printf("2 - Listar as bandas\n");
			printf("3 - Pesquisa banda pelo ranking\n");
			printf("4 - Pesquisa banda pelo tipo de música\n");
			printf("5 - Pesquisa banda pelo nome\n");
			printf("6 - Encerra o programa\n");
			printf("Escolha: ");
			scanf("%d", &an);
		if(an >= 1 && an <= 6) break;
		else{
			clear();
			continue;
		}
	}

	return an;
}


int rankQuery(Banda *content, int tam, int desejado){
	//realiza query por rank, retornando index do item
	int index, i;

	for(i = 0; i < tam; i++){
		if(i == tam - 1){
			if(content[i].ranking == desejado) break;
			else{
				return -1;
			}
		}
		if(content[i].ranking == desejado) break;
	}
	// printf("QUERY: %d\n", i);
	return i;
}


int genreQuery(Banda *content, int tam, char *desejado){
	// realiza query do genero
	int index, i;

	for(i = 0; i < tam; i++){
		if(i == tam - 1){
			if(!(strcmp(content[i].genero, desejado))) break;
			else{
				return -1;
			}
		}
		if(!(strcmp(content[i].genero, desejado))) break;
	}
	// printf("QUERY: %d\n", i);
	return i;
}


int nameQuery(Banda *content, int tam, char *desejado){
	//realiza query do nome da banda
	int index, i;

	for(i = 0; i < tam; i++){
		if(i == tam - 1){
			if(!(strcmp(content[i].nome, desejado))) break;
			else{
				return -1;
			}
		}
		if(!(strcmp(content[i].nome, desejado))) break;
	}
	// printf("QUERY: %d\n", i);
	return i;
}

int printQuery(Banda *content, int tam, char *desejado){
	//printa query, cada item
	int index, i;

	for(i = 0; i < tam; i++){
		if(i == tam - 1){
			if(!(strcmp(content[i].genero, desejado))){
				printf("%-16s%-16s%-16d%-15d\n", content[i].nome, content[i].genero, content[i].integrantes, content[i].ranking);
			}
			else{
				return -1;
			}
		}
		else if(!(strcmp(content[i].genero, desejado))){
			printf("%-16s%-16s%-16d%-15d\n", content[i].nome, content[i].genero, content[i].integrantes, content[i].ranking);
		}
	}
	// printf("QUERY: %d\n", i);
	return i;
}


int printQueryName(Banda *content, int tam, char *desejado){
	//printa query, cada item
	int index, i;

	for(i = 0; i < tam; i++){
		if(i == tam - 1){
			if(!(strcmp(content[i].nome, desejado))){
				printf("%-16s%-16s%-16d%-15d\n", content[i].nome, content[i].genero, content[i].integrantes, content[i].ranking);
			}
			else{
				return -1;
			}
		}
		else if(!(strcmp(content[i].nome, desejado))){
			printf("%-16s%-16s%-16d%-15d\n", content[i].nome, content[i].genero, content[i].integrantes, content[i].ranking);
		}
	}
	// printf("QUERY: %d\n", i);
	return i;
}

void showBandbyID(Banda *content, int tam, int id){
	//mostra bandas pelo index para rankQUERY
	clear();
	printf("Banda(s) Pesquisada(s): \n");
	printf("%-15s|%-15s|%-15s|%-15s\n", "Nome", "Genero", "Integrantes", "Ranking");
	printf("-------------------------------------------------------\n");
	printf("%-16s%-16s%-16d%-15d\n", content[id].nome, content[id].genero, content[id].integrantes, content[id].ranking);
	printf("-------------------------------------------------------\n");
	printf("\n");
}
