#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "_util.h"

#define LIMITE_STRING 100
#define LIMITE_FUNC 100
#define LIMITE_RG 40
#define LIMITE_NUM 10
#define QTD_MENU 12

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
void ListaFuncionarios(TipoCadastro listagem, const char *nomeTela);
void OrdenaNome(TipoCadastro listagem);
void OrdenaSalario(TipoCadastro listagem);
void InicioSalarioIntervalo(TipoCadastro cadastro);
void SalarioIntervalo(TipoCadastro cadastro, double v1, double v2);
void CalculaImposto(TipoCadastro cadastro);
void InicioBuscaNome(TipoCadastro cadastro);
TipoReg BuscaNome(TipoCadastro lista, const char *nome);
void InicioAtualizaSalario(TipoCadastro *cadastro);
TipoReg BuscaRG(TipoCadastro lista, const char *rg, int *indiceEncontrado);
void InicioBuscaMaraja(TipoCadastro cadastro);
TipoReg ListaMaraja(TipoCadastro cadastro);
void InicioRemoveFuncionario(TipoCadastro *cadastro);
bool RemoveFuncionario(TipoCadastro *cadastro, const char *rg);
void InicioListaAniversarioMes(TipoCadastro cadastro);
void ListaAniversarioMes(TipoCadastro cadastro, int mes);
void InicioFiltraTudo(TipoCadastro cadastro);
void ListaAniversarioSexo(TipoCadastro cadastro, int dia, int mes, int ano, char sexo);
void limpaBuffer();

int main(void)
{
    TipoCadastro cadastro = IniciaCadastro();
    setlocale(LC_ALL, "Portuguese");

    char *menu[QTD_MENU] = {
        "Cadastro",
        "Listagem",
        "Ordenar por nome",
        "Ordenar por sal�rio",
        "Intervalo de sal�rios",
        "C�lculo de impostos",
        "Busca por nome",
        "Atualiza��o de sal�rio",
        "Maior sal�rio",
        "Remove funcion�rio",
        "Lista aniversariantes do m�s",
        "Filtragem por anivers�rio e sexo"};
    int dec;

    // dados para teste//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    strcpy(cadastro.funcionarios[0].nome, "Eduardo");
    strcpy(cadastro.funcionarios[0].rg, "6807");
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
    cadastro.funcionarios[3].dataNascimento.mes = 3;
    cadastro.funcionarios[3].dataNascimento.ano = 2006;

    cadastro.quant++;

    // dados para teste//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
            ListaFuncionarios(cadastro, "geral");
            break;
        case 2:
            OrdenaNome(cadastro);
            break;
        case 3:
            OrdenaSalario(cadastro);
            break;
        case 4:
            InicioSalarioIntervalo(cadastro);
            break;
        case 5:
            CalculaImposto(cadastro);
            break;
        case 6:
            InicioBuscaNome(cadastro);
            break;
        case 7:
            InicioAtualizaSalario(&cadastro);
            break;
        case 8:
            InicioBuscaMaraja(cadastro);
            break;
        case 9:
            InicioRemoveFuncionario(&cadastro);
            break;
        case 10:
            InicioListaAniversarioMes(cadastro);
            break;
        case 11:
            InicioFiltraTudo(cadastro);
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
    printf("Quantidade de funcion?rios a serem cadastrados: ");
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

void ListaFuncionarios(TipoCadastro listagem, const char *nomeTela)
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
    printf("Lista de funcion�rios - %s", nomeTela);

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

void OrdenaNome(TipoCadastro listagem)
{
    if (listagem.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

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

    ListaFuncionarios(ordenado, "ordenada por nome");
}

void OrdenaSalario(TipoCadastro listagem)
{
    if (listagem.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

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

    ListaFuncionarios(ordenado, "ordenada por sal�rio");
}

void InicioSalarioIntervalo(TipoCadastro cadastro)
{
    if (cadastro.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");

    gotoxy(3, 3);
    printf("Intervalo de sal?rios");

    char numStr[LIMITE_NUM];
    int v1;
    gotoxy(3, 5);
    printf("Valor inferior: ");
    fgets(numStr, sizeof numStr, stdin);
    v1 = atof(numStr);

    int v2;
    gotoxy(3, 7);
    printf("Valor superior: ");
    fgets(numStr, sizeof numStr, stdin);
    v2 = atof(numStr);

    SalarioIntervalo(cadastro, v1, v2);
}

void SalarioIntervalo(TipoCadastro cadastro, double v1, double v2)
{
    if (v1 > v2)
    {
        double aux = v1;
        v1 = v2;
        v2 = v1;
    }

    TipoCadastro filtrado;
    filtrado.quant = 0;

    for (int i = 0; i < cadastro.quant; i++)
    {
        if (cadastro.funcionarios[i].salario > v1 && cadastro.funcionarios[i].salario < v2)
        {
            filtrado.funcionarios[filtrado.quant++] = cadastro.funcionarios[i];
        }
    }

    double media, soma = 0;

    for (int i = 0; i < filtrado.quant; i++)
    {
        soma += filtrado.funcionarios[i].salario;
    }

    media = soma / filtrado.quant;

    gotoxy(3, 10);
    printf("Resultado: R$%.2lf", media);

    gotoxy(3, 28);
    system("pause");
}

void CalculaImposto(TipoCadastro cadastro)
{
    if (cadastro.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    gotoxy(3, 3);
    printf("C?LCULO DE IMPOSTO");

    char *p;
    char nome[LIMITE_STRING + 1] = {0};
    gotoxy(3, 5);
    printf("Insira o nome que ser? buscado: ");
    fgets(nome, LIMITE_STRING, stdin);
    p = strchr(nome, '\n');
    if (p)
        *p = 0;

    TipoReg registro;
    bool encontrou = false;

    for (int i = 0; i < cadastro.quant; i++)
    {
        if (strcmp(cadastro.funcionarios[i].nome, nome) == 0)
        {
            registro = cadastro.funcionarios[i];
            encontrou = true;
            break;
        }
    }

    if (!encontrou)
    {
        gotoxy(3, 7);
        printf("Funcion?rio n?o encontrado...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    if (registro.salario < 1000)
    {
        gotoxy(3, 7);
        printf("O valor do sal?rio n?o prev? pagamento de imposto...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    double valorImposto;

    if (registro.salario < 2000)
    {
        valorImposto = registro.salario / 10;
    }
    else if (registro.salario < 3500)
    {
        valorImposto = (registro.salario / 20) * 3;
    }
    else
    {
        valorImposto = registro.salario / 4;
    }

    gotoxy(3, 7);
    printf("Valor do pagamento: R$%.2lf", valorImposto);

    gotoxy(3, 28);
    system("pause");

    return;
}

void InicioBuscaNome(TipoCadastro cadastro)
{
    if (cadastro.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    gotoxy(3, 3);
    printf("BUSCA POR NOME");

    char *p;
    char nome[LIMITE_STRING + 1] = {0};
    gotoxy(3, 5);
    printf("Insira o nome que ser� buscado: ");
    fgets(nome, LIMITE_STRING, stdin);
    p = strchr(nome, '\n');
    if (p)
        *p = 0;

    TipoReg registro;

    registro = BuscaNome(cadastro, nome);

    if (strcmp(registro.nome, "") == 0)
    {
        gotoxy(3, 7);
        printf("Funcion�rio n�o encontrado...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    gotoxy(3, 7);
    printf("Nome do funcion�rio: %s", registro.nome);

    gotoxy(3, 8);
    printf("RG: %s", registro.rg);

    gotoxy(3, 9);
    printf("Sal�rio: R$%.2lf", registro.salario);

    gotoxy(3, 10);
    printf("Idade: %d anos", registro.idade);

    gotoxy(3, 11);
    printf("G�nero: %c", registro.sexo);

    gotoxy(3, 12);
    printf("%02d/%02d/%04d",
           registro.dataNascimento.dia,
           registro.dataNascimento.mes,
           registro.dataNascimento.ano);

    gotoxy(3, 28);
    system("pause");
}

TipoReg BuscaNome(TipoCadastro lista, const char *nome)
{
    for (int i = 0; i < lista.quant; i++)
    {
        if (strcmp(nome, lista.funcionarios[i].nome) == 0)
        {
            return lista.funcionarios[i];
        }
    }

    TipoReg vazio;
    strcpy(vazio.nome, "");
    return vazio;
}

void InicioAtualizaSalario(TipoCadastro *cadastro)
{
    if ((*cadastro).quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");

    gotoxy(3, 3);
    printf("ATUALIZA��O DE SAL�RIO");

    char *p;
    char rg[LIMITE_RG];
    gotoxy(3, 5);
    printf("Insira o RG do funcion�rio que ter� o sal�rio atualizado: ");
    fgets(rg, LIMITE_STRING, stdin);
    p = strchr(rg, '\n');
    if (p)
        *p = 0;

    TipoReg registro;
    int indice = -1;

    registro = BuscaRG(*cadastro, rg, &indice);

    if (indice == -1)
    {
        gotoxy(3, 7);
        printf("Funcion�rio n�o encontrado...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    gotoxy(3, 7);
    printf("Funcion�rio: %s", registro.nome);

    double novoSalario;
    char numStr[LIMITE_NUM];
    gotoxy(3, 10);
    printf("Novo sal�rio: ");
    fgets(numStr, sizeof numStr, stdin);
    novoSalario = atof(numStr);

    (*cadastro).funcionarios[indice].salario = novoSalario;

    gotoxy(3, 13);
    printf("Sal�rio atualizado com sucesso!");

    gotoxy(3, 28);
    system("pause");
}

TipoReg BuscaRG(TipoCadastro lista, const char *rg, int *indiceEncontrado)
{
    for (int i = 0; i < lista.quant; i++)
    {
        if (strcmp(rg, lista.funcionarios[i].rg) == 0)
        {
            *indiceEncontrado = i;
            return lista.funcionarios[i];
        }
    }

    TipoReg vazio;
    strcpy(vazio.rg, "");
    return vazio;
}

void InicioBuscaMaraja(TipoCadastro cadastro)
{
    if (cadastro.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");

    gotoxy(3, 3);
    printf("MAIOR SAL�RIO");

    TipoReg registro = ListaMaraja(cadastro);

    gotoxy(3, 7);
    printf("Nome do funcion�rio: %s", registro.nome);

    gotoxy(3, 8);
    printf("RG: %s", registro.rg);

    gotoxy(3, 9);
    printf("Sal�rio: R$%.2lf", registro.salario);

    gotoxy(3, 10);
    printf("Idade: %d anos", registro.idade);

    gotoxy(3, 11);
    printf("G�nero: %c", registro.sexo);

    gotoxy(3, 12);
    printf("%02d/%02d/%04d",
           registro.dataNascimento.dia,
           registro.dataNascimento.mes,
           registro.dataNascimento.ano);

    gotoxy(3, 28);
    system("pause");
}

TipoReg ListaMaraja(TipoCadastro cadastro)
{
    TipoReg funcResult;
    double salarioResult = -1;

    for (int i = 0; i < cadastro.quant; i++)
    {
        if (cadastro.funcionarios[i].salario > salarioResult)
        {
            salarioResult = cadastro.funcionarios[i].salario;
            funcResult = cadastro.funcionarios[i];
        }
    }

    return funcResult;
}

void InicioRemoveFuncionario(TipoCadastro *cadastro)
{
    if ((*cadastro).quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");

    gotoxy(3, 3);
    printf("REMO��O DE FUNCION�RIO");

    char *p;
    char rg[LIMITE_RG];
    gotoxy(3, 5);
    printf("Insira o RG do funcion�rio que ser� exclu�do: ");
    fgets(rg, LIMITE_STRING, stdin);
    p = strchr(rg, '\n');
    if (p)
        *p = 0;

    if (!RemoveFuncionario(cadastro, rg))
    {
        gotoxy(3, 7);
        printf("Funcion�rio n�o encontrado...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    gotoxy(3, 7);
    printf("Funcion�rio removido com sucesso!");

    gotoxy(3, 28);
    system("pause");

    return;
}

bool RemoveFuncionario(TipoCadastro *cadastro, const char *rg)
{
    TipoReg empty;

    for (int i = 0; i < (*cadastro).quant; i++)
    {
        if (strcmp(rg, (*cadastro).funcionarios[i].rg) == 0)
        {

            for (i; i < (*cadastro).quant - 1; i++)
            {
                (*cadastro).funcionarios[i] = (*cadastro).funcionarios[i + 1];
            }

            (*cadastro).funcionarios[i] = empty;
            (*cadastro).quant -= 1;
            return true;
        }
    }

    return false;
}

void InicioListaAniversarioMes(TipoCadastro cadastro)
{
    if (cadastro.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");

    gotoxy(3, 3);
    printf("LISTA ANIVERS�RIO NO M�S");

    char numStr[LIMITE_NUM];
    int mes;
    gotoxy(3, 5);
    printf("M�s a ser pesquisado (1-12): ");
    fgets(numStr, sizeof numStr, stdin);
    mes = atof(numStr);

    ListaAniversarioMes(cadastro, mes);
}

void ListaAniversarioMes(TipoCadastro cadastro, int mes)
{
    TipoCadastro filtrada;
    filtrada.quant = 0;

    for (int i = 0; i < cadastro.quant; i++)
    {
        if (cadastro.funcionarios[i].dataNascimento.mes == mes)
        {
            filtrada.funcionarios[filtrada.quant] = cadastro.funcionarios[i];
            filtrada.quant++;
        }
    }

    if (filtrada.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");
    ListaFuncionarios(filtrada, "Funcion�rios que fazem anivers�rio nesse m�s");
}

void InicioFiltraTudo(TipoCadastro cadastro)
{
    if (cadastro.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");

    gotoxy(3, 3);
    printf("LISTA DE FILTRAGEM GERAL");

    char numStr[LIMITE_NUM];
    int dia;
    gotoxy(3, 5);
    printf("Dia: ");
    fgets(numStr, sizeof numStr, stdin);
    dia = atof(numStr);

    numStr[LIMITE_NUM];
    int mes;
    gotoxy(3, 7);
    printf("M�s: ");
    fgets(numStr, sizeof numStr, stdin);
    mes = atof(numStr);

    numStr[LIMITE_NUM];
    int ano;
    gotoxy(3, 9);
    printf("Ano: ");
    fgets(numStr, sizeof numStr, stdin);
    ano = atof(numStr);

    char sexo;
    gotoxy(3, 11);
    printf("Sexo (m/f): ");
    sexo = fgetc(stdin);

    ListaAniversarioSexo(cadastro, dia, mes, ano, sexo);
}

void ListaAniversarioSexo(TipoCadastro cadastro, int dia, int mes, int ano, char sexo)
{
    TipoCadastro filtrada;
    filtrada.quant = 0;

    for (int i = 0; i < cadastro.quant; i++)
    {
        if (cadastro.funcionarios[i].dataNascimento.dia == dia &&
            cadastro.funcionarios[i].dataNascimento.mes == mes &&
            cadastro.funcionarios[i].dataNascimento.ano == ano &&
            cadastro.funcionarios[i].sexo == sexo)
        {
            filtrada.funcionarios[filtrada.quant] = cadastro.funcionarios[i];
            filtrada.quant++;
        }
    }

    if (filtrada.quant == 0)
    {
        gotoxy(3, 3);
        printf("Lista vazia...");

        gotoxy(3, 28);
        system("pause");

        return;
    }

    system("cls");
    ListaFuncionarios(filtrada, "Funcion�rios filtrados");
}

void limpaBuffer()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
