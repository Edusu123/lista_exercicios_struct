#include <locale.h>
#include <stdio.h>
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
        case 1:
        case 2:
        case 3:
        default:
            break;
        }
    } while (dec < 4);
}

void cadastro(banda listaBandas[LIMITE_BANDAS], int *indiceInicial)
{
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
        scanf("%s", novaBanda.nomeBanda);

        gotoxy(3, 8);
        printf("Tipo de música: ");
        fflush(stdin);
        scanf("%s", novaBanda.genMusica);

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
