/*
/* Aluno: Vinicius Barbosa de Medeiros
/* Cadeira: Introdução a Programação - 2017.1
/* 
/* Instruções:
/* Para uso no WINDOWS:
/*	- Comente a(s) linha(s) -> 30.
/*	- Descomente a(s) linha(s) -> 31, 60, 128.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#define NNOTAS 3 // Numero de notas

// Struct do Aluno
struct aluno{
	int matricula;
	char nome[150];
	double notas[NNOTAS];
	double media;
}Aluno; // cria um struct GLOBAL para facilitar

// ------ Funções ------

// limpa tela - precisa ser ajustado para uso no windows
void clear( void ){
	system("clear"); // uso EXCLUSIVO LINUX
	// system("cls"); // uso EXCLUSIVO WINDOWS
}

// funções que cuidam do menu e da opção do usuario
void menu( void ); // exibe menu
int escolha( void ); // captura opção do usuario

// funções que gerenciam o usuario com arquivo
int inserirAlunos(char *name); // adiciona novo aluno no arquivo
double media(double *valores, int nValores); //calcula media
int nEstudantes(char *name); //calcula numero de estudantes postos no arquivo
int exibaEstudante(char *filename); //exibe todos os estudantes

// funções QUERY -> matricula
int getMatricula(void); //recebe e valida numero de matricula
int exibaEstudanteMATRICULA(char *filename, int matricula); // exibe estudantes com a matricula recebida

// funções QUERY -> nome
int getNome(char *nome); //recebe e valida nome
int exibaEstudanteNOME(char *filename, char *nome); // exibe estudante com o nome recebido

// funções QUERY -> media
int getRangeNOTA(double *min, double *max); // recebe intervaldo de medias
int exibaEstudanteMEDIA(char *filename, double min, double max); // exibe estudantes dentro do intervaldo determinado

// ---------------------

// ------ MAIN ------ 
int main(){
	// setlocale(LC_ALL, "Portuguese"); //USO EXCLUSIVO NO WINDOWS
	int opcao;
	int on = 1;
	int nAlunos;
	int mat;
	double min, max;
	char nome[1001];

	char *filename = "alunos.txt"; // nome do arquivo

	while(on){ // comeca programa
		menu(); //exibe menu
		opcao = escolha(); //recebe opcao do menu
		clear(); // limpa tela

		// insere alunos
		if(opcao == 1){

			printf("Inserir dados\n");
			printf("Parar de adicionar alunos, bote a matricula 0\n");
			printf("Aperte ENTER para começar.\n");
			getchar();
			getchar();

			if(inserirAlunos(filename)){ // caso o arquivo não abra
				on = 0; // acaba loop
				return 1; //return 1 para main
			}
		}

		// lista alunos
		else if(opcao == 2){
			if((nAlunos = nEstudantes(filename))  == 0){ // caso nao exista alunos cadastrados
				clear();
				printf("Nenhum Aluno foi encontrado. Tente adicionar algum.\n");
			}
			else{ // exibe estudante
				exibaEstudante(filename); 
			}

		}

		// lista pela matricula
		else if(opcao == 3){
			mat = getMatricula(); // recebe matricula a ser pesquisada
			exibaEstudanteMATRICULA(filename, mat); //exibe resuldado
		}

		// lista pelo nome
		else if(opcao == 4){
			getNome(nome); // recebe nome a ser pesquisado
			printf("Nome: %s\n", nome); //printa nome
			exibaEstudanteNOME(filename, nome); //exibe resultado
		}

		// lista por media - RANGE
		else if(opcao == 5){
			getRangeNOTA(&min, &max); // recebe intervalo de media a ser pesquisado
			exibaEstudanteMEDIA(filename, min, max); // exibe resultado
		}

		// encerra programa
		else if(opcao == 6){
			on = 0;
			break;
		}
	}

	// system("pause"); //USO EXCLUSIVO NO WINDOWS
	return 0;
}


void menu( void ){
	printf("MENU: \n");
	printf("1 - Inserir alunos\n");
	printf("2 - Listar alunos\n");
	printf("3 - Pesquisar alunos pela matricula\n");
	printf("4 - Pesquisar alunos pelo nome\n");
	printf("5 - Pesquisar alunos por uma média (minimo e maximo)\n");
	printf("6 - Encerrar\n");
}

int escolha( void ){
	int an;
	while(1){
		printf("Escolha sua opção: ");
		scanf("%d", &an);

		if(an >= 1 && an <= 6){
			return an;
			break;
		}
		else{
			printf("Esse opção não é válida. Tente novamente.\n");
		}
	}
}

int inserirAlunos( char *name ){
	int i = 1, n = 0;

	FILE *arquivo;
	arquivo = fopen(name, "a");

	if(!arquivo){
		printf("Não foi possivel abrir o arquivo.\n");
		return 1;
	}
	while(1){
		clear();
		printf("Matricula do aluno %d: ", i);
		scanf("%d", &Aluno.matricula);

		if(Aluno.matricula == 0){
			break;
		}

		printf("Nome do aluno %d: ", i);
		scanf("%s", Aluno.nome);

		for(n = 0; n < NNOTAS; n++){
			printf("Nota %d do aluno %d: ", n + 1, i);
			scanf("%lf", &Aluno.notas[n]);
		}

		Aluno.media = media(Aluno.notas, NNOTAS);

		// fwrite(&Aluno, sizeof(Aluno), 1, arquivo);
		fprintf(arquivo,"%d %s %.1lf %.1lf %.1lf %.1lf\n", 
			Aluno.matricula,
			Aluno.nome, 
			Aluno.notas[0],
			Aluno.notas[1],
			Aluno.notas[2],
			Aluno.media);

		i++;
	}
	fclose(arquivo);
	return 0;
}

double media(double *valores, int nValores){
	double total = 0;
	int i;
	for(i = 0; i < nValores; i++){
		total += valores[i];
	}

	return (double)(total/nValores);
}

int nEstudantes( char *name){
	FILE *arquivo;

	int nL = 0;
	char c;

	arquivo = fopen(name, "r");

	if(!arquivo){
		printf("Não foi possivel abrir o arquivo.\n");
		return -1;
	}

	do{
		c = fgetc(arquivo);

		if(feof(arquivo)){
			break;
		}

		if(c == '\n'){
			nL++;
		}
	}while(1);

	return nL;
}

int exibaEstudante(char *filename){
	FILE *arquivo;
	arquivo = fopen(filename, "r");

	if(!arquivo){
		printf("Não foi possivel abrir o arquivo.\n");
		return -1;
	}
	int i;
	printf("Alunos: \n");
	printf("-------- ------------  ----------------- -------\n");
	printf("%7s%10s%17s%13s\n", "Matri.", "Nome", "Notas", "Media");
	printf("-------- ------------  ----------------- -------\n");

	while((fscanf(arquivo, "%d %s %lf %lf %lf %lf",
		&Aluno.matricula,
		Aluno.nome, 
		&Aluno.notas[0],
		&Aluno.notas[1],
		&Aluno.notas[2],
		&Aluno.media)) != EOF){
		printf("%4d%15s%9.1lf%5.1lf%5.1lf%8.1lf\n", 
			Aluno.matricula, 
			Aluno.nome, 
			Aluno.notas[0], 
			Aluno.notas[1], 
			Aluno.notas[2], 
			Aluno.media
			);
	}
	printf("-------- ------------  ----------------- -------\n");
}

int getMatricula(void){
	int mat;
	while(1){
		printf("Digite uma matricula para pesquisar: ");
		scanf("%d", &mat);
		if(mat > 0){
			return mat;
			break;
		}
		else{
			printf("Digite uma matricula válida.\n");
		}
	}
}

int exibaEstudanteMATRICULA(char *filename, int matricula){
	int controle = 0;
	FILE *arquivo;
	arquivo = fopen(filename, "r");

	if(!arquivo){
		printf("Não foi possivel abrir o arquivo.\n");
		return -1;
	}
	
	printf("Alunos: \n");
	printf("-------- ------------  ----------------- -------\n");
	printf("%7s%10s%17s%13s\n", "Matri.", "Nome", "Notas", "Media");
	printf("-------- ------------  ----------------- -------\n");

	while((fscanf(arquivo, "%d %s %lf %lf %lf %lf",
		&Aluno.matricula,
		Aluno.nome, 
		&Aluno.notas[0],
		&Aluno.notas[1],
		&Aluno.notas[2],
		&Aluno.media)) != EOF){
		if(Aluno.matricula == matricula){
		printf("%4d%15s%9.1lf%5.1lf%5.1lf%8.1lf\n", 
				Aluno.matricula, 
				Aluno.nome, 
				Aluno.notas[0], 
				Aluno.notas[1], 
				Aluno.notas[2], 
				Aluno.media
				);
		controle++;
		}
	}
	printf("-------- ------------  ----------------- -------\n");
	if(controle == 0){
		printf("Não foi encontrado nenhum aluno com a matricula %d.\nTente Novamente\n", matricula);
	}
}

int getNome(char *nome){
	char query[1001];
	while(1){
		printf("Digite um nome para ser pesquisado: ");
		scanf("%s", query);
		if(strlen(query) > 0){
			strcpy(nome, query);
			return 1;
			break;
		}
		else{
			printf("Digite um nome válido\n");
		}
	}
}

int exibaEstudanteNOME(char *filename, char *nome){
	int controle = 0;
		FILE *arquivo;
		arquivo = fopen(filename, "r");

		if(!arquivo){
			printf("Não foi possivel abrir o arquivo.\n");
			return -1;
		}
		
		printf("Alunos: \n");
		printf("-------- ------------  ----------------- -------\n");
		printf("%7s%10s%17s%13s\n", "Matri.", "Nome", "Notas", "Media");
		printf("-------- ------------  ----------------- -------\n");

		while((fscanf(arquivo, "%d %s %lf %lf %lf %lf",
			&Aluno.matricula,
			Aluno.nome, 
			&Aluno.notas[0],
			&Aluno.notas[1],
			&Aluno.notas[2],
			&Aluno.media)) != EOF){
			if(!(strcmp(Aluno.nome, nome))){
			printf("%4d%15s%9.1lf%5.1lf%5.1lf%8.1lf\n", 
					Aluno.matricula, 
					Aluno.nome, 
					Aluno.notas[0], 
					Aluno.notas[1], 
					Aluno.notas[2], 
					Aluno.media
					);
			controle++;
			}
		}
		printf("-------- ------------  ----------------- -------\n");
		if(controle == 0){
			printf("Não foi encontrado nenhum aluno com o nome %s.\nTente Novamente\n", nome);
		}
}

int getRangeNOTA(double *min, double *max){
	double a, b;
	while(1){
		printf("Digite um intervalo de medias para pesquisar (min max): ");
		scanf("%lf %lf", &a, &b);
		if(a >= 0 && b >= 0){
			if(a > b){
				*min = b;
				*max = a;
			}
			else{
				// b > a
				*min = a;
				*max = b;
			}
			return 0;
		}
		else{
			printf("Digite um intervalo válido.\n");
		}
	}
}

int exibaEstudanteMEDIA(char *filename, double min, double max){
	int controle = 0;
		FILE *arquivo;
		arquivo = fopen(filename, "r");

		if(!arquivo){
			printf("Não foi possivel abrir o arquivo.\n");
			return -1;
		}
		
		printf("Alunos: \n");
		printf("-------- ------------  ----------------- -------\n");
		printf("%7s%10s%17s%13s\n", "Matri.", "Nome", "Notas", "Media");
		printf("-------- ------------  ----------------- -------\n");

		while((fscanf(arquivo, "%d %s %lf %lf %lf %lf",
			&Aluno.matricula,
			Aluno.nome, 
			&Aluno.notas[0],
			&Aluno.notas[1],
			&Aluno.notas[2],
			&Aluno.media)) != EOF){
			if(Aluno.media >= min && Aluno.media <= max){
			printf("%4d%15s%9.1lf%5.1lf%5.1lf%8.1lf\n", 
					Aluno.matricula, 
					Aluno.nome, 
					Aluno.notas[0], 
					Aluno.notas[1], 
					Aluno.notas[2], 
					Aluno.media
					);
			controle++;
			}
		}
		printf("-------- ------------  ----------------- -------\n");
		if(controle == 0){
			printf("Não foi encontrado nenhum aluno nesse intervalo de média.\nTente Novamente\n");
		}
}
