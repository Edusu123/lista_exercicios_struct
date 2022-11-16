#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "_util.h"

#define LIMITE_STRING 100
#define LIMITE_FUNC 100
#define LIMITE_RG 10
#define LIMITE_NUM 10
#define QTD_MENU 2

typedef struct
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct
{
    char nome[LIMITE_STRING];
    char rg[LIMITE_RG];
    double salario;
    int idade;
    char sexo;
    data dataNascimento;
} TipoReg;

typedef struct
{
    TipoReg funcionarios[LIMITE_FUNC];
    int quant;
} TipoCadastro;

TipoCadastro IniciaCadastro();
TipoCadastro LeFuncionarios(TipoCadastro atual);
void ListaFuncionarios(TipoCadastro listagem);
void limpaBuffer();

int main(void)
{
    TipoCadastro cadastro = IniciaCadastro();
    setlocale(LC_ALL, "Portuguese");

    char *menu[QTD_MENU] = {"Cadastro", "Listagem"};
    int dec;

    strcpy(cadastro.funcionarios[0].nome, "Eduardo Conde Pires");
    strcpy(cadastro.funcionarios[0].rg, "52.900.680-7");
    cadastro.funcionarios[0].salario = 12000.0;
    cadastro.funcionarios[0].sexo = 'm';
    cadastro.funcionarios[0].dataNascimento.dia = 6;
    cadastro.funcionarios[0].dataNascimento.mes = 2;
    cadastro.funcionarios[0].dataNascimento.ano = 2003;

    cadastro.quant++;

    do
    {
        dec = geraMenu("Exerc�cios finais", "GERENCIADOR DE FUNCION�RIOS", menu, QTD_MENU);
        system("cls");

        switch (dec)
        {
        case 0:
            cadastro = LeFuncionarios(cadastro);
            break;
        case 1:
            ListaFuncionarios(cadastro);
            break;
        default:
            break;
        }
    } while (dec < QTD_MENU);

    return 0;
}

TipoCadastro IniciaCadastro()
{
    TipoCadastro retorno;
    retorno.quant = 0;
    return retorno;
}

TipoCadastro LeFuncionarios(TipoCadastro atual)
{
    char numStr[LIMITE_NUM];
    int qtdFuncionarios;
    cursorVisivel(true);
    gotoxy(3, 5);
    printf("Quantidade de funcion�rios a serem cadastrados: ");
    fgets(numStr, sizeof numStr, stdin);
    qtdFuncionarios = atoi(numStr);

    for (int i = 0; i < qtdFuncionarios; i++)
    {
        TipoReg novoFuncionario;
        system("cls");

        gotoxy(3, 5);
        printf("Funcion�rio %02d", atual.quant + 1);

        gotoxy(3, 7);
        printf("Nome do funcion�rio: ");
        fgets(novoFuncionario.nome, sizeof novoFuncionario.nome, stdin);

        gotoxy(3, 8);
        printf("RG: ");
        fgets(novoFuncionario.rg, sizeof novoFuncionario.rg, stdin);

        gotoxy(3, 9);
        printf("Sal�rio: ");
        limpaBuffer();
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.salario = atof(numStr);

        gotoxy(3, 10);
        printf("Idade: ");
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.idade = atoi(numStr);

        gotoxy(3, 11);
        printf("G�nero (m/f/n/o): ");
        novoFuncionario.sexo = fgetc(stdin);

        gotoxy(3, 12);
        printf("Data de nascimento: ");
        gotoxy(5, 13);
        printf("Dia: ");
        limpaBuffer();
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.dataNascimento.dia = atoi(numStr);
        gotoxy(5, 14);
        printf("M�s: ");
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.dataNascimento.mes = atoi(numStr);
        gotoxy(5, 15);
        printf("Ano: ");
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.dataNascimento.ano = atoi(numStr);

        atual.funcionarios[atual.quant++] = novoFuncionario;
    }

    return atual;
}

void ListaFuncionarios(TipoCadastro listagem)
{
    if (listagem.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    gotoxy(3, 3);
    printf("Lista de funcion�rios");

    const int colunaNome = 3, colunaRG = 25, colunaSalario = 40, colunaIdade = 55, colunaSexo = 65, colunaDataNascimento = 70;

    gotoxy(colunaNome, 5);
    printf("Nome");
    gotoxy(colunaRG, 5);
    printf("RG");
    gotoxy(colunaSalario, 5);
    printf("Sal�rio");
    gotoxy(colunaIdade, 5);
    printf("Idade");
    gotoxy(colunaSexo, 5);
    printf("Sexo");
    gotoxy(colunaDataNascimento, 5);
    printf("Data de nascimento");

    int index = 7;

    for (int i = 0; i < listagem.quant; i++)
    {
        gotoxy(colunaNome, index);
        printf("%s", listagem.funcionarios[i].nome);

        gotoxy(colunaRG, index);
        printf("%s", listagem.funcionarios[i].rg);

        gotoxy(colunaSalario, index);
        printf("R$%.2lf", listagem.funcionarios[i].salario);

        gotoxy(colunaIdade, index);
        printf("%d", listagem.funcionarios[i].idade);

        gotoxy(colunaSexo, index);
        printf("%c", listagem.funcionarios[i].sexo);

        gotoxy(colunaDataNascimento, index);
        printf("%02d/%02d/%04d",
               listagem.funcionarios[i].dataNascimento.dia,
               listagem.funcionarios[i].dataNascimento.mes,
               listagem.funcionarios[i].dataNascimento.ano);

        index++;
    }

    gotoxy(3, 28);
    system("pause");
}

void limpaBuffer()
{
    while (getchar() != '\n')
        ;
}
