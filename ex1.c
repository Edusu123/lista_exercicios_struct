#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "_util.h"

#define LIMITE_STRING 100
#define LIMITE_BANDAS 100
#define QTD_MENU 4

typedef struct
{
    char nomeBanda[LIMITE_STRING];
    char genMusica[LIMITE_STRING];
    int numeroIntegrantes;
    int posicao;
} banda;

void cadastro(banda listaBandas[LIMITE_BANDAS], int *indiceInicial);
void listaPorRanking(banda listaBandas[LIMITE_BANDAS], int quantidadeBandas);
void buscaPorNome(banda listaBandas[LIMITE_BANDAS], int quantidadeBandas);
void verificaRanking(banda listaBandas[LIMITE_BANDAS], int quantidadeBandas);

void main()
{
    setlocale(LC_ALL, "Portuguese");

    char *menu[QTD_MENU] = {"Cadastro", "Busca por ranking", "Busca por nome", "Banda favorita"};
    banda listaBandas[LIMITE_BANDAS];
    int dec, indiceInicialParaCadastro = 0;

    do
    {
        dec = geraMenu("Exercício 1", "Gerenciador de bandas", menu, QTD_MENU);
        system("cls");

        switch (dec)
        {
        case 0:
            cadastro(listaBandas, &indiceInicialParaCadastro);
            break;
        case 1:
            listaPorRanking(listaBandas, indiceInicialParaCadastro);
            break;
        case 2:
            buscaPorNome(listaBandas, indiceInicialParaCadastro);
            break;
        case 3:
            verificaRanking(listaBandas, indiceInicialParaCadastro);
            break;
        default:
            break;
        }
    } while (dec < 4);
}

void cadastro(banda listaBandas[LIMITE_BANDAS], int *indiceInicial)
{
    char end = '\0';
    int qtdBandas;
    gotoxy(3, 5);
    printf("Quantidade de bandas a cadastrar: ");
    scanf("%d", &qtdBandas);

    for (int i = 0; i < qtdBandas; i++)
    {
        banda novaBanda;
        system("cls");

        gotoxy(3, 5);
        printf("Banda #%02d", *indiceInicial + 1);

        gotoxy(3, 7);
        printf("Nome da banda: ");
        fflush(stdin);
        fgets(novaBanda.nomeBanda, 100, stdin);
        strncat(novaBanda.nomeBanda, &end, 1);

        gotoxy(3, 8);
        printf("Tipo de música: ");
        fflush(stdin);
        fgets(novaBanda.genMusica, 100, stdin);
        strncat(novaBanda.genMusica, &end, 1);

        gotoxy(3, 9);
        printf("Número de integrantes: ");
        scanf("%d", &novaBanda.numeroIntegrantes);

        gotoxy(3, 10);
        printf("Posição no ranking (0 para fora do ranking): ");
        scanf("%d", &novaBanda.posicao);

        listaBandas[*indiceInicial] = novaBanda;
        (*indiceInicial)++;
    }
}

void listaPorRanking(banda listaBandas[LIMITE_BANDAS], int quantidadeBandas)
{
    int ranking;

    do
    {
        system("cls");

        gotoxy(3, 5);
        printf("Ranking da banda a ser pesquisado: ");
        scanf("%d", &ranking);
    } while (ranking < 1 && ranking > 5);

    banda bandaSelecionada;
    bool selecionado = false;

    for (int i = 0; i < quantidadeBandas; i++)
    {
        if (listaBandas[i].posicao == ranking)
        {
            selecionado = true;
            bandaSelecionada = listaBandas[i];
        }
    }

    system("cls");

    if (!selecionado)
    {
        gotoxy(3, 7);
        printf("A banda não foi encontrada...");
        system("pause>NUL");
        return;
    }

    gotoxy(3, 5);
    printf("Banda: %s", bandaSelecionada.nomeBanda);

    gotoxy(3, 6);
    printf("Gênero musical: %s", bandaSelecionada.genMusica);

    gotoxy(3, 7);
    printf("Número de integrantes: %d", bandaSelecionada.numeroIntegrantes);

    system("pause>NUL");
}

void buscaPorNome(banda listaBandas[LIMITE_BANDAS], int quantidadeBandas)
{
    char nomePesquisa[LIMITE_STRING];
    bool selecionado = false;
    banda bandaSelecionada;

    system("cls");
    gotoxy(3, 5);
    printf("Insira o nome da banda a buscar: ");
    fflush(stdin);
    fgets(nomePesquisa, 100, stdin);

    for (int i = 0; i < quantidadeBandas; i++)
    {
        if (strcmp(nomePesquisa, listaBandas[i].nomeBanda) == 0)
        {
            selecionado = true;
            bandaSelecionada = listaBandas[i];
        }
    }

    system("cls");

    if (!selecionado)
    {
        gotoxy(3, 7);
        printf("A banda não foi encontrada...");
        system("pause>NUL");
        return;
    }

    gotoxy(3, 5);
    printf("Banda: %s", bandaSelecionada.nomeBanda);

    gotoxy(3, 6);
    printf("Gênero musical: %s", bandaSelecionada.genMusica);

    gotoxy(3, 7);
    printf("Número de integrantes: %d", bandaSelecionada.numeroIntegrantes);

    system("pause>NUL");
}

void verificaRanking(banda listaBandas[LIMITE_BANDAS], int quantidadeBandas)
{
    char nomePesquisa[LIMITE_STRING];
    bool encontrada = false;
    int pos;

    system("cls");

    gotoxy(3, 5);
    printf("Insira o nome da banda a buscar: ");
    fflush(stdin);
    fgets(nomePesquisa, 100, stdin);

    for (int i = 0; i < quantidadeBandas; i++)
    {
        if (strcmp(nomePesquisa, listaBandas[i].nomeBanda) == 0 && listaBandas[i].posicao != 0)
        {
            pos = listaBandas[i].posicao;
            encontrada = true;
        }
    }

    gotoxy(3, 7);

    if (encontrada)
    {
        printf("A banda está no ranking, na posição %02d", pos);
    }
    else
    {
        printf("A banda não está no ranking...");
    }

    system("pause>NUL");
}
