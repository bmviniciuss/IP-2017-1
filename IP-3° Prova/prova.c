/*
/*  - Terceira prova
/*  - Aluno: Vinicius Barbosa de Medeiros
/*  - Cadeira: Introdução a Programação
/*
/*  INTRUÇÕES USO NO WINDOWS:
/*  COMENTAR LINHA(S) -> 31.
/*  DESCOMENTAR LINHA(S) -> 32,52, 102.
/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define NNOTAS 3

const char *filename = "CADASTRO.txt";

struct cadastro{
    int matricula;
    char nome[16];
    double nota1;
    double nota2;
    double nota3;
    double media;
};

void clear( void ){
    system("clear"); // uso no linux
    // system("cls"); // uso no windows
}

void menu( void );
int getOpcao( void );

void insereAlunos(struct cadastro Aluno, const char *filename);

int hasData(const char *filename);
void listarAlunos(struct cadastro Aluno, const char *filename);

void getNome(char *nome);
int hasNome(const char *filename, char *nome, struct cadastro Aluno);
void listarAlunosNome(struct cadastro Aluno, const char *filename, char *nome);

void getIntervalo(double *min, double *max);
int hasMedia(const char *filename, double min, double max, struct cadastro Aluno);
void listarAlunosMedia(const char *filename,struct cadastro Aluno, double min, double max);

int main(){
    // setlocale(LC_ALL, "Portuguese"); //Uso no windows
    struct cadastro Aluno;
    int op, on = 1;
    char nome[100];
    double min = 0, max = 0;

    while(on){
        menu();
        op = getOpcao();

        if(op == 1){
            // inserir alunos
            clear();
            insereAlunos(Aluno, filename);
        }
        else if(op == 2){
            // listar alunos
            clear();
            if(hasData(filename)){
                listarAlunos(Aluno, filename);
            }
            else{
                printf("Não há alunos cadastrados. Tente inserir algum.\n");
            }
        }
        else if(op == 3){
            // pesquisar alunos por nome
            clear();
            getNome(nome);
            if(hasNome(filename, nome, Aluno)){
                listarAlunosNome(Aluno, filename, nome);
            }
            else{
                printf("Não há nenhum aluno cadastrado com esse nome.\n");
            }

        }
        else if(op == 4){
            //pesquisar alunos por media (intervalo)
            clear();
            getIntervalo(&min, &max);
            if(hasMedia(filename, min, max, Aluno)){
                listarAlunosMedia(filename, Aluno, min, max);
            }
            else{
                printf("Não há nenhum aluno cadastrado com media dentro do intervalo dado.\n");
            }
        }
        else{
            printf("Saindo...\n");
            on = 0;
        }
    }

    // system("pause"); // USO NO WINDOWS
    return 0;
}

void menu( void ){
    printf("Menu: \n");
    printf("1 - Inserir Alunos\n");
    printf("2 - Listar Alunos\n");
    printf("3 - Pesquisar Alunos pelo nome\n");
    printf("4 - Pesquisar Alunos por média\n");
    printf("5 - Sair\n");
}

int getOpcao( void ){
    int op;

    while(1){
        printf("Qual opção você deseja: ");
        scanf("%d", &op);

        if(op >= 1 && op <= 5){
            return op;
            break;
        }
        else{
            printf("Digite um valor valor válido. Tente novamente\n");
        }

    }
}

void insereAlunos(struct cadastro Aluno, const char *filename){
    int i = 1;
    FILE *arquivo;

    double total = 0, media = 0;

    if((arquivo = fopen(filename, "a")) == NULL){
        printf("Não foi possivel abrir o arquivo. Tente novamente\n");
    }
    while(1){
        clear();
        total = 0;
        media = 0;
        printf("Matricula do Aluno %d (0 - Encerra): ", i);
        scanf("%d", &Aluno.matricula);

        if(Aluno.matricula == 0){
            break;
        }

        printf("Nome do Aluno %d: ", i);
        scanf("%s", Aluno.nome);

        while(1){
            printf("Nota 1 do Aluno %d: ", i);
            scanf("%lf", &Aluno.nota1);

            if(Aluno.nota1 >= 0){
                break;
            }
            else{
                printf("Esse nota não é válida. Tente novamente.\n");
            }
        }

        while(1){
            printf("Nota 2 do Aluno %d: ", i);
            scanf("%lf", &Aluno.nota2);

            if(Aluno.nota2 >= 0){
                break;
            }
            else{
                printf("Esse nota não é válida. Tente novamente.\n");
            }
        }

        while(1){
            printf("Nota 3 do Aluno %d: ", i);
            scanf("%lf", &Aluno.nota3);

            if(Aluno.nota3 >= 0){
                break;
            }
            else{
                printf("Esse nota não é válida. Tente novamente.\n");
            }
        }

        total = Aluno.nota1 + Aluno.nota2 + Aluno.nota3;
        media = (double)total / NNOTAS;

        Aluno.media = media;

        fprintf(arquivo, "%d %s %.1lf %.1lf %.1lf %.1lf\n",
        Aluno.matricula,
        Aluno.nome,
        Aluno.nota1,
        Aluno.nota2,
        Aluno.nota3,
        Aluno.media);

        i++;
    }

    fclose(arquivo);
}

int hasData(const char *filename){
    FILE *arquivo;
    char c;
    int n = 0;
    if((arquivo = fopen(filename, "a+")) == NULL){
        printf("Não foi possivel abrir esse arquivo.\n");
        return -1;
    }

    while((c = fgetc(arquivo)) != EOF){
        if(c == '\n'){
            n++;
        }
    }

    fclose(arquivo);
    return n;
}

void listarAlunos(struct cadastro Aluno, const char *filename){
    double med1 = 0, med2 = 0, med3 = 0, medGeral = 0;
    double n = 0;
    FILE *arquivo;

    if((arquivo = fopen(filename, "r")) == NULL){
        printf("Nã foi possivel abrir esse arquivo\n");
    }
    else{
        printf("------   ----------   --------    --------    --------    --------\n");
        // printf("Matr     Nome         Nota1       Nota2       Nota3       Media\n", );
        printf("%4s%9s%14s%12s%12s%12s\n", "Matr", "Nome", "Nota1", "Nota2", "Nota3", "Media");
        printf("------   ----------   --------    --------    --------    --------\n");
        while((fscanf(arquivo, "%d %s %lf %lf %lf %lf\n", &Aluno.matricula, Aluno.nome,
        &Aluno.nota1, &Aluno.nota2, &Aluno.nota3,
        &Aluno.media)) != EOF){
            printf("%3d%15s%10.1lf%12.1lf%12.1lf%12.1lf\n",
                                                    Aluno.matricula,
                                                    Aluno.nome,
                                                    Aluno.nota1,
                                                    Aluno.nota2,
                                                    Aluno.nota3,
                                                    Aluno.media);
            med1 += Aluno.nota1;
            med2 += Aluno.nota2;
            med3 += Aluno.nota3;
            medGeral += Aluno.media;
            n++;
        }
        med1 /= n;
        med2 /= n;
        med3 /= n;
        medGeral /= n;
        printf("------   ----------   --------    --------    --------    --------\n");
        // printf("   Media Geral          10.0        10.0        10.0        10.0\n");
        printf("%14s%14.1lf%12.1lf%12.1lf%12.1lf\n", "Media Geral", med1, med2, med3, medGeral);
        printf("------   ----------   --------    --------    --------    --------\n");
    }

    fclose(arquivo);
}

void getNome(char *nome){
    while (1) {
        printf("Nome que deseja pesquisar: ");
        scanf("%s", nome);

        if((strlen(nome)) > 1){
            break;
        }
        else{
            printf("Digite um nome válido.\n");
        }
    }
}

int hasNome(const char *filename, char *nome, struct cadastro Aluno){
    FILE *arquivo;

    if((arquivo = fopen(filename, "r")) == NULL){
        printf("Nã foi possivel abrir esse arquivo\n");
        return -1;
    }
    else{
        while((fscanf(arquivo, "%d %s %lf %lf %lf %lf\n", &Aluno.matricula, Aluno.nome,
        &Aluno.nota1, &Aluno.nota2, &Aluno.nota3,
        &Aluno.media)) != EOF){
            if(!(strcmp(Aluno.nome, nome))){
                return 1;
            }
        }

    }
    return 0;
    fclose(arquivo);
}

void listarAlunosNome(struct cadastro Aluno, const char *filename, char *nome){
    FILE *arquivo;

    if((arquivo = fopen(filename, "r")) == NULL){
        printf("Nã foi possivel abrir esse arquivo\n");
    }
    else{
        printf("------   ----------   --------    --------    --------    --------\n");
        // printf("Matr     Nome         Nota1       Nota2       Nota3       Media\n", );
        printf("%4s%9s%14s%12s%12s%12s\n", "Matr", "Nome", "Nota1", "Nota2", "Nota3", "Media");
        printf("------   ----------   --------    --------    --------    --------\n");
        while((fscanf(arquivo, "%d %s %lf %lf %lf %lf\n", &Aluno.matricula, Aluno.nome,
        &Aluno.nota1, &Aluno.nota2, &Aluno.nota3,
        &Aluno.media)) != EOF){
            if(!(strcmp(Aluno.nome, nome))){
                printf("%3d%15s%10.1lf%12.1lf%12.1lf%12.1lf\n",
                Aluno.matricula,
                Aluno.nome,
                Aluno.nota1,
                Aluno.nota2,
                Aluno.nota3,
                Aluno.media);
            }
        }
        printf("------   ----------   --------    --------    --------    --------\n");
    }

    fclose(arquivo);
}

void getIntervalo(double *min, double *max){
    double minLocal, maxLocal;
    printf("Digite um intervalo de medias para ser pesquisado\n");
    while(1){
        printf("Media minima: ");
        scanf("%lf", &minLocal);

        if(minLocal >= 0){
            *min = minLocal;
            break;
        }
        else{
            printf("Digite uma nota válida.\n");
        }
    }
    while (1) {
        printf("Media maxima: ");
        scanf("%lf", &maxLocal);

        if(maxLocal >= 0 && maxLocal >= minLocal){
            *max = maxLocal;
            break;
        }
        else if(minLocal > maxLocal){
            printf("A nota maxima precisa ser maior ou igual que a minima.\n");
        }
        else{
            printf("Digite uma nota válida.\n");
        }
    }
}

int hasMedia(const char *filename, double min, double max, struct cadastro Aluno){
    FILE *arquivo;

    if((arquivo = fopen(filename, "r")) == NULL){
        printf("Nã foi possivel abrir esse arquivo\n");
        return -1;
    }
    else{
        while((fscanf(arquivo, "%d %s %lf %lf %lf %lf\n", &Aluno.matricula, Aluno.nome,
        &Aluno.nota1, &Aluno.nota2, &Aluno.nota3,
        &Aluno.media)) != EOF){
            if((Aluno.media >= min) && (Aluno.media <= max) ){
                return 1;
            }
        }

    }
    return 0;
    fclose(arquivo);
}

void listarAlunosMedia(const char *filename,struct cadastro Aluno, double min, double max){
    FILE *arquivo;

    if((arquivo = fopen(filename, "r")) == NULL){
        printf("Nã foi possivel abrir esse arquivo\n");
    }
    else{
        printf("------   ----------   --------    --------    --------    --------\n");
        // printf("Matr     Nome         Nota1       Nota2       Nota3       Media\n", );
        printf("%4s%9s%14s%12s%12s%12s\n", "Matr", "Nome", "Nota1", "Nota2", "Nota3", "Media");
        printf("------   ----------   --------    --------    --------    --------\n");
        while((fscanf(arquivo, "%d %s %lf %lf %lf %lf\n", &Aluno.matricula, Aluno.nome,
        &Aluno.nota1, &Aluno.nota2, &Aluno.nota3,
        &Aluno.media)) != EOF){
            if((Aluno.media >= min) && (Aluno.media <= max) ){
                printf("%3d%15s%10.1lf%12.1lf%12.1lf%12.1lf\n",
                Aluno.matricula,
                Aluno.nome,
                Aluno.nota1,
                Aluno.nota2,
                Aluno.nota3,
                Aluno.media);
            }
        }
        printf("------   ----------   --------    --------    --------    --------\n");
    }

    fclose(arquivo);
}
