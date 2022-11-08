#include <locale.h>
#include <stdio.h>
#include <windows.h>

#include "_util.h"

#define LIMITE_STRING 100
#define LIMITE_FUNC 100
#define LIMITE_RG 10

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

int main(void)
{
    TipoCadastro cadastro = IniciaCadastro();
    setlocale(LC_ALL, "Portuguese");

    return 0;
}

TipoCadastro IniciaCadastro()
{
    TipoCadastro retorno;
    retorno.quant = 0;
    return retorno;
}
