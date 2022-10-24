#include <locale.h>
#include <stdio.h>
#include <windows.h>

#include "_util.h"

struct Ponto
{
    int x;
    int y;
};

typedef struct Ponto ponto;

void main()
{
    setlocale(LC_ALL, "Portuguese");

    system("cls");

    ponto v1, v2, ponto;
    gotoxy(3, 5);
    printf("Insira as coordenadas do retângulo: ");

    gotoxy(3, 7);
    printf("Canto inferior esquerdo: ");

    gotoxy(3, 8);
    printf("X: ");
    scanf("%d", &v1.x);

    gotoxy(3, 9);
    printf("Y: ");
    scanf("%d", &v1.y);

    gotoxy(3, 11);
    printf("Canto superior direito: ");

    gotoxy(3, 12);
    printf("X: ");
    scanf("%d", &v2.x);

    gotoxy(3, 13);
    printf("Y: ");
    scanf("%d", &v2.y);

    gotoxy(3, 15);
    printf("Novo ponto: ");

    gotoxy(3, 16);
    printf("X: ");
    scanf("%d", &ponto.x);

    gotoxy(3, 17);
    printf("Y: ");
    scanf("%d", &ponto.y);

    gotoxy(5, 20);

    if (ponto.x >= v1.x && ponto.y >= v1.y && ponto.x <= v2.x && ponto.y <= v2.y)
    {
        printf("O ponto está dentro do retângulo!");
    }
    else
    {
        printf("O ponto está fora do retângulo...");
    }

    gotoxy(5, 23);
    system("pause");
    system("cls");
}
