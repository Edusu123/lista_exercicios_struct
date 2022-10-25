#include <locale.h>
#include <stdio.h>
#include <windows.h>

#include "_util.h"

#define QTD_MENU 6

typedef struct
{
    int num;
    int den;
} fracao;

void leituraFracao();
void leitura(fracao *frac);

void main()
{
    setlocale(LC_ALL, "Portuguese");

    char *menu[QTD_MENU] = {"Leitura", "Soma", "Subtração", "Multiplicação", "Dividir", "Simplificar"};
    int dec;

    do
    {
        dec = geraMenu("Exercício 4", "Frações", menu, QTD_MENU);
        system("cls");

        switch (dec)
        {
        case 0:
            leituraFracao();
            break;
        default:
            break;
        }
    } while (dec < QTD_MENU);
}

void leituraFracao()
{
    fracao frac;

    system("cls");

    gotoxy(3, 5);
    printf("Leitura dos elementos da fração");

    leitura(&frac);

    gotoxy(3, 11);
    printf("Lido: %d/%d", frac.num, frac.den);

    gotoxy(3, 13);
    system("pause");
}

void leitura(fracao *frac)
{
    gotoxy(3, 7);
    printf("Numerador: ");
    scanf("%d", &(frac->num));

    gotoxy(3, 9);
    printf("Denominador: ");
    scanf("%d", &(frac->den));
}
