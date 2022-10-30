#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "_util.h"

#define MAX_STRING 100
#define MAX_ESTADO 2
#define MAX_CEP 8
#define MAX_RG 10
#define MAX_ALUNOS 100
#define QTD_MENU 5

typedef struct
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct
{
    char rua[MAX_STRING];
    char cidade[MAX_STRING];
    char estado[MAX_ESTADO];
    char cep[MAX_CEP];
} endereco;

typedef struct
{
    char nome[MAX_STRING];
    data nascimento;
    char rg[MAX_RG];
    char sexo;
    endereco enderec;
    int ra;
    double cr;
} aluno;

void leituraAluno(aluno listaAlunos[MAX_ALUNOS], int *indice);
void ordenaPorNome(aluno listaAlunos[MAX_ALUNOS], int indice);
void ordenaPorCR(aluno listaAlunos[MAX_ALUNOS], int indice);
void pesquisaPorRA(aluno listaAlunos[MAX_ALUNOS], int indice);
void listagemGeral(aluno listaAlunos[MAX_ALUNOS], int indice);

void main()
{
    setlocale(LC_ALL, "Portuguese");

    char *menu[QTD_MENU] = {"Novo aluno", "Ordenar por nome", "Ordenar por CR", "Pesquisa por RA", "Listagem geral"};
    aluno listaAlunos[MAX_ALUNOS];
    int dec, indice = 0;

    do
    {
        dec = geraMenu("Exercício 4", "Gerenciamento de alunos", menu, QTD_MENU);
        system("cls");

        switch (dec)
        {
        case 0:
            leituraAluno(listaAlunos, &indice);
            break;
        case 1:
            ordenaPorNome(listaAlunos, indice);
            break;
        case 2:
            ordenaPorCR(listaAlunos, indice);
            break;
        case 3:
            pesquisaPorRA(listaAlunos, indice);
            break;
        case 4:
            listagemGeral(listaAlunos, indice);
            break;
        default:
            break;
        }

    } while (dec < QTD_MENU);
}

void leituraAluno(aluno listaAlunos[MAX_ALUNOS], int *indice)
{
    int qtdAlunos;
    gotoxy(3, 5);
    printf("Quantidade de alunos a serem cadastrados: ");
    fflush(stdin);
    scanf("%d", &qtdAlunos);

    for (int i = 0; i < qtdAlunos; i++)
    {
        aluno novoAluno;
        system("cls");

        gotoxy(3, 5);
        printf("Aluno #%02d", *indice + 1);

        gotoxy(3, 7);
        printf("Nome do aluno: ");
        fflush(stdin);
        fgets(novoAluno.nome, MAX_STRING, stdin);

        gotoxy(3, 8);
        printf("Data de nascimento: ");

        gotoxy(7, 9);
        printf("Dia: ");
        fflush(stdin);
        scanf("%d", &novoAluno.nascimento.dia);

        gotoxy(7, 10);
        printf("Mês: ");
        fflush(stdin);
        scanf("%d", &novoAluno.nascimento.mes);

        gotoxy(7, 11);
        printf("Ano: ");
        fflush(stdin);
        scanf("%d", &novoAluno.nascimento.ano);

        gotoxy(3, 12);
        printf("RG: ");
        fflush(stdin);
        fgets(novoAluno.rg, MAX_RG, stdin);

        gotoxy(3, 13);
        printf("Sexo: ");
        fflush(stdin);
        scanf("%c", &novoAluno.sexo);

        gotoxy(3, 14);
        printf("Endereço: ");

        gotoxy(7, 15);
        printf("Nome da rua: ");
        fflush(stdin);
        fgets(novoAluno.enderec.rua, MAX_STRING, stdin);

        gotoxy(7, 16);
        printf("Nome da cidade: ");
        fflush(stdin);
        fgets(novoAluno.enderec.cidade, MAX_STRING, stdin);

        gotoxy(7, 17);
        printf("Nome do estado: ");
        fflush(stdin);
        fgets(novoAluno.enderec.estado, MAX_ESTADO, stdin);

        gotoxy(7, 18);
        printf("CEP: ");
        fflush(stdin);
        fgets(novoAluno.enderec.cep, MAX_CEP, stdin);

        gotoxy(3, 19);
        printf("RA: ");
        fflush(stdin);
        scanf("%d", &novoAluno.ra);

        gotoxy(3, 20);
        printf("Coeficiente de Rendimento: ");
        fflush(stdin);
        scanf("%lf", &novoAluno.cr);

        listaAlunos[(*indice)++] = novoAluno;
    }
}

void ordenaPorNome(aluno listaAlunos[MAX_ALUNOS], int indice)
{
    if (indice == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    aluno listaCopia[MAX_ALUNOS];

    for (int i = 0; i < indice; i++)
    {
        listaCopia[i] = listaAlunos[i];
    }

    for (int i = 0; i < indice; i++)
    {
        for (int j = 0; j < indice - 1; j++)
        {
            if (strcmp(listaCopia[j].nome, listaCopia[j + 1].nome) > 0)
            {
                aluno aux = listaCopia[j];
                listaCopia[j] = listaCopia[j + 1];
                listaCopia[j + 1] = aux;
            }
        }
    }

    gotoxy(3, 3);
    printf("Lista ordenada alfabeticamente");

    const int colunaNome = 3, colunaRA = 25, colunaCR = 30, colunaRG = 36;

    gotoxy(colunaNome, 5);
    printf("Nome");
    gotoxy(colunaRA, 5);
    printf("RA");
    gotoxy(colunaCR, 5);
    printf("CR");
    gotoxy(colunaRG, 5);
    printf("RG");

    int index = 7;

    for (int i = 0; i < indice; i++)
    {
        gotoxy(colunaNome, index);
        printf("%s", listaCopia[i].nome);

        gotoxy(colunaRA, index);
        printf("%03d", listaCopia[i].ra);

        gotoxy(colunaCR, index);
        printf("%.2lf", listaCopia[i].cr);

        gotoxy(colunaRG, index);
        printf("%s", listaCopia[i].rg);

        index++;
    }

    gotoxy(3, 28);
    system("pause");
}

void ordenaPorCR(aluno listaAlunos[MAX_ALUNOS], int indice)
{
    if (indice == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    aluno listaCopia[MAX_ALUNOS];

    for (int i = 0; i < indice; i++)
    {
        listaCopia[i] = listaAlunos[i];
    }

    for (int i = 0; i < indice; i++)
    {
        for (int j = 0; j < indice - 1; j++)
        {
            if (listaCopia[j].cr < listaCopia[j + 1].cr)
            {
                aluno aux = listaCopia[j];
                listaCopia[j] = listaCopia[j + 1];
                listaCopia[j + 1] = aux;
            }
        }
    }

    gotoxy(3, 3);
    printf("Lista ordenada por Coeficiente de Rendimento");

    const int colunaNome = 3, colunaRA = 25, colunaCR = 30, colunaRG = 36;

    gotoxy(colunaNome, 5);
    printf("Nome");
    gotoxy(colunaRA, 5);
    printf("RA");
    gotoxy(colunaCR, 5);
    printf("CR");
    gotoxy(colunaRG, 5);
    printf("RG");

    int index = 7;

    for (int i = 0; i < indice; i++)
    {
        gotoxy(colunaNome, index);
        printf("%s", listaCopia[i].nome);

        gotoxy(colunaRA, index);
        printf("%03d", listaCopia[i].ra);

        gotoxy(colunaCR, index);
        printf("%.2lf", listaCopia[i].cr);

        gotoxy(colunaRG, index);
        printf("%s", listaCopia[i].rg);

        index++;
    }

    gotoxy(3, 28);
    system("pause");
}

void pesquisaPorRA(aluno listaAlunos[MAX_ALUNOS], int indice)
{
    int raPesquisa;
    bool encontrado = false;
    aluno alunoPesquisa;

    gotoxy(3, 3);
    printf("RA a ser pesquisado: ");
    scanf("%d", &raPesquisa);

    for (int i = 0; i < indice; i++)
    {
        if (listaAlunos[i].ra == raPesquisa)
        {
            encontrado = true;
            alunoPesquisa = listaAlunos[i];
        }
    }

    if (!encontrado)
    {
        gotoxy(3, 5);
        printf("Não foi encontrado nenhum aluno...");

        gotoxy(3, 30);
        system("pause");

        return;
    }

    gotoxy(3, 7);
    printf("Nome do aluno: %s", alunoPesquisa.nome);

    gotoxy(3, 8);
    printf("Data de nascimento: %02d/%02d/%04d", alunoPesquisa.nascimento.dia, alunoPesquisa.nascimento.mes, alunoPesquisa.nascimento.ano);

    gotoxy(3, 9);
    printf("RG: %s", alunoPesquisa.rg);

    gotoxy(3, 10);
    printf("Sexo: %c", alunoPesquisa.sexo);

    gotoxy(3, 11);
    printf("Endereço: ");

    gotoxy(7, 12);
    printf("Nome da rua: %s", alunoPesquisa.enderec.rua);

    gotoxy(7, 13);
    printf("Nome da cidade: %s", alunoPesquisa.enderec.cidade);

    gotoxy(7, 14);
    printf("Nome do estado: %s", alunoPesquisa.enderec.estado);

    gotoxy(7, 15);
    printf("CEP: %s", alunoPesquisa.enderec.cep);

    gotoxy(3, 16);
    printf("RA: %d", alunoPesquisa.ra);

    gotoxy(3, 17);
    printf("Coeficiente de Rendimento: %.2lf", alunoPesquisa.cr);

    gotoxy(3, 20);
    system("pause");
}

void listagemGeral(aluno listaAlunos[MAX_ALUNOS], int indice)
{
    if (indice == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    const int colunaNome = 3, colunaRA = 25, colunaCR = 30, colunaRG = 36;

    gotoxy(colunaNome, 5);
    printf("Nome");
    gotoxy(colunaRA, 5);
    printf("RA");
    gotoxy(colunaCR, 5);
    printf("CR");
    gotoxy(colunaRG, 5);
    printf("RG");

    int index = 7;

    for (int i = 0; i < indice; i++)
    {
        gotoxy(colunaNome, index);
        printf("%s", listaAlunos[i].nome);

        gotoxy(colunaRA, index);
        printf("%03d", listaAlunos[i].ra);

        gotoxy(colunaCR, index);
        printf("%.2lf", listaAlunos[i].cr);

        gotoxy(colunaRG, index);
        printf("%s", listaAlunos[i].rg);

        index++;
    }

    gotoxy(3, 28);
    system("pause");
}
