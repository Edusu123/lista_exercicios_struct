#include <locale.h>
#include <stdio.h>
#include <windows.h>

#include "_util.h"

#define QTD_MENU 4

typedef struct
{
    int a;
    int b;
} complexo;

void leituraComplexo();
void somaComplexo();
void subtracaoComplexo();
void multiplicacaoComplexo();
void leitura(complexo *comp);

void main()
{
    setlocale(LC_ALL, "Portuguese");

    char *menu[QTD_MENU] = {"Leitura", "Soma", "Subtração", "Multiplicação"};
    int dec;

    do
    {
        dec = geraMenu("Exercício 3", "Números complexos", menu, QTD_MENU);
        system("cls");

        switch (dec)
        {
        case 0:
            leituraComplexo();
            break;
        case 1:
            somaComplexo();
            break;
        case 2:
            subtracaoComplexo();
            break;
        case 3:
            multiplicacaoComplexo();
        default:
            break;
        }
    } while (dec < 4);
}

void leituraComplexo()
{
    complexo comp;

    system("cls");

    gotoxy(3, 5);
    printf("Leitura de números complexos");

    leitura(&comp);

    gotoxy(3, 11);
    printf("Lido: z = %d + %di", comp.a, comp.b);

    gotoxy(3, 13);
    system("pause");
}

void somaComplexo()
{
    complexo comp1, comp2, result;

    system("cls");

    gotoxy(3, 5);
    printf("Número #01");

    leitura(&comp1);

    system("cls");

    gotoxy(3, 5);
    printf("Número #02");

    leitura(&comp2);

    result.a = comp1.a + comp2.a;
    result.b = comp1.b + comp2.b;

    system("cls");

    gotoxy(3, 5);
    printf("Resultado: z = %d + %di", result.a, result.b);

    gotoxy(3, 7);
    system("pause");
}

void subtracaoComplexo()
{
    complexo comp1, comp2, result;

    system("cls");

    gotoxy(3, 5);
    printf("Número #01");

    leitura(&comp1);

    system("cls");

    gotoxy(3, 5);
    printf("Número #02");

    leitura(&comp2);

    result.a = comp1.a - comp2.a;
    result.b = comp1.b - comp2.b;

    system("cls");

    gotoxy(3, 5);
    printf("Resultado: z = %d + %di", result.a, result.b);

    gotoxy(3, 7);
    system("pause");
}

void multiplicacaoComplexo()
{
    complexo comp1, comp2, result;

    system("cls");

    gotoxy(3, 5);
    printf("Número #01");

    leitura(&comp1);

    system("cls");

    gotoxy(3, 5);
    printf("Número #02");

    leitura(&comp2);

    result.a = (comp1.a * comp2.a) - (comp1.b * comp2.b);
    result.b = (comp1.a * comp2.b) + (comp1.b * comp2.a);

    system("cls");

    gotoxy(3, 5);
    printf("Resultado: z = %d + %di", result.a, result.b);

    gotoxy(3, 7);
    system("pause");
}

void leitura(complexo *comp)
{
    gotoxy(3, 7);
    printf("Parte inteira: ");
    scanf("%d", &(comp->a));

    gotoxy(3, 9);
    printf("Parte complexa: ");
    scanf("%d", &(comp->b));
}
