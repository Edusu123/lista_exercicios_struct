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
#define QTD_MENU 4

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
void OrdenaNome(TipoCadastro listagem);
void OrdenaSalario(TipoCadastro listagem);
void limpaBuffer();

int main(void)
{
    TipoCadastro cadastro = IniciaCadastro();
    setlocale(LC_ALL, "Portuguese");

    char *menu[QTD_MENU] = {"Cadastro", "Listagem", "Ordenar por nome", "Ordenar por salário"};
    int dec;

    // dados para teste//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    strcpy(cadastro.funcionarios[0].nome, "Eduardo");
    strcpy(cadastro.funcionarios[0].rg, "52.900.680-7");
    cadastro.funcionarios[0].salario = 12000.0;
    cadastro.funcionarios[0].idade = 19;
    cadastro.funcionarios[0].sexo = 'm';
    cadastro.funcionarios[0].dataNascimento.dia = 6;
    cadastro.funcionarios[0].dataNascimento.mes = 2;
    cadastro.funcionarios[0].dataNascimento.ano = 2003;

    cadastro.quant++;

    strcpy(cadastro.funcionarios[1].nome, "Matheus");
    strcpy(cadastro.funcionarios[1].rg, "52.900.680-8");
    cadastro.funcionarios[1].salario = 13000.0;
    cadastro.funcionarios[1].idade = 20;
    cadastro.funcionarios[1].sexo = 'm';
    cadastro.funcionarios[1].dataNascimento.dia = 6;
    cadastro.funcionarios[1].dataNascimento.mes = 2;
    cadastro.funcionarios[1].dataNascimento.ano = 2004;

    cadastro.quant++;

    strcpy(cadastro.funcionarios[2].nome, "Amauri");
    strcpy(cadastro.funcionarios[2].rg, "52.900.680-9");
    cadastro.funcionarios[2].salario = 11000.0;
    cadastro.funcionarios[2].idade = 21;
    cadastro.funcionarios[2].sexo = 'm';
    cadastro.funcionarios[2].dataNascimento.dia = 6;
    cadastro.funcionarios[2].dataNascimento.mes = 2;
    cadastro.funcionarios[2].dataNascimento.ano = 2005;

    cadastro.quant++;

    strcpy(cadastro.funcionarios[3].nome, "Patricia");
    strcpy(cadastro.funcionarios[3].rg, "52.900.681-0");
    cadastro.funcionarios[3].salario = 14000.0;
    cadastro.funcionarios[3].idade = 22;
    cadastro.funcionarios[3].sexo = 'f';
    cadastro.funcionarios[3].dataNascimento.dia = 6;
    cadastro.funcionarios[3].dataNascimento.mes = 2;
    cadastro.funcionarios[3].dataNascimento.ano = 2006;

    cadastro.quant++;

    // dados para teste//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    do
    {
        dec = geraMenu("Exercícios finais", "GERENCIADOR DE FUNCIONÁRIOS", menu, QTD_MENU);
        system("cls");

        switch (dec)
        {
        case 0:
            cadastro = LeFuncionarios(cadastro);
            break;
        case 1:
            ListaFuncionarios(cadastro);
            break;
        case 2:
            OrdenaNome(cadastro);
            break;
        case 3:
            OrdenaSalario(cadastro);
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
    printf("Quantidade de funcionï¿½rios a serem cadastrados: ");
    fgets(numStr, sizeof numStr, stdin);
    qtdFuncionarios = atoi(numStr);

    for (int i = 0; i < qtdFuncionarios; i++)
    {
        TipoReg novoFuncionario;
        system("cls");

        gotoxy(3, 5);
        printf("Funcionï¿½rio %02d", atual.quant + 1);

        gotoxy(3, 7);
        printf("Nome do funcionï¿½rio: ");
        fgets(novoFuncionario.nome, sizeof novoFuncionario.nome, stdin);

        gotoxy(3, 8);
        printf("RG: ");
        fgets(novoFuncionario.rg, sizeof novoFuncionario.rg, stdin);

        gotoxy(3, 9);
        printf("Salï¿½rio: ");
        limpaBuffer();
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.salario = atof(numStr);

        gotoxy(3, 10);
        printf("Idade: ");
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.idade = atoi(numStr);

        gotoxy(3, 11);
        printf("Gï¿½nero (m/f/n/o): ");
        novoFuncionario.sexo = fgetc(stdin);

        gotoxy(3, 12);
        printf("Data de nascimento: ");
        gotoxy(5, 13);
        printf("Dia: ");
        limpaBuffer();
        fgets(numStr, sizeof numStr, stdin);
        novoFuncionario.dataNascimento.dia = atoi(numStr);
        gotoxy(5, 14);
        printf("Mï¿½s: ");
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
    printf("Lista de funcionï¿½rios");

    const int colunaNome = 3, colunaRG = 25, colunaSalario = 40, colunaIdade = 55, colunaSexo = 65, colunaDataNascimento = 70;

    gotoxy(colunaNome, 5);
    printf("Nome");
    gotoxy(colunaRG, 5);
    printf("RG");
    gotoxy(colunaSalario, 5);
    printf("Salário");
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

void OrdenaNome(TipoCadastro listagem)
{
    TipoCadastro ordenado;
    ordenado.quant = listagem.quant;

    for (int i = 0; i < listagem.quant; i++)
    {
        ordenado.funcionarios[i] = listagem.funcionarios[i];
    }

    for (int i = 0; i < ordenado.quant; i++)
    {
        for (int j = 0; j < ordenado.quant - i - 1; j++)
        {
            if (strcmp(ordenado.funcionarios[j].nome, ordenado.funcionarios[j + 1].nome) > 0)
            {
                TipoReg aux = ordenado.funcionarios[j];
                ordenado.funcionarios[j] = ordenado.funcionarios[j + 1];
                ordenado.funcionarios[j + 1] = aux;
            }
        }
    }

    ListaFuncionarios(ordenado);
}

void OrdenaSalario(TipoCadastro listagem)
{
    TipoCadastro ordenado;
    ordenado.quant = listagem.quant;

    for (int i = 0; i < listagem.quant; i++)
    {
        ordenado.funcionarios[i] = listagem.funcionarios[i];
    }

    for (int i = 0; i < ordenado.quant; i++)
    {
        for (int j = 0; j < ordenado.quant - i - 1; j++)
        {
            if (ordenado.funcionarios[j].salario > ordenado.funcionarios[j + 1].salario)
            {
                TipoReg aux = ordenado.funcionarios[j];
                ordenado.funcionarios[j] = ordenado.funcionarios[j + 1];
                ordenado.funcionarios[j + 1] = aux;
            }
        }
    }

    ListaFuncionarios(ordenado);
}

void limpaBuffer()
{
    while (getchar() != '\n')
        ;
}
