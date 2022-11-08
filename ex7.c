#include <locale.h>
#include <stdio.h>
#include <windows.h>

#include "_util.h"

struct vetor
{
    float x;
    float y;
    float z;
};

typedef struct vetor vet;

void limpaBuffer();

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    system("cls");

    vet vet1, vet2, result;
    char numStr[5];

    gotoxy(3, 3);
    printf("SOMADOR DE VETORES");

    gotoxy(3, 5);
    printf("Vetor 1:");
    gotoxy(5, 6);
    printf("X: ");
    fgets(numStr, sizeof numStr, stdin);
    vet1.x = atof(numStr);
    gotoxy(5, 7);
    printf("Y: ");
    fgets(numStr, sizeof numStr, stdin);
    vet1.y = atof(numStr);
    gotoxy(5, 8);
    printf("Z: ");
    fgets(numStr, sizeof numStr, stdin);
    vet1.z = atof(numStr);

    // limpaBuffer();

    gotoxy(3, 10);
    printf("Vetor 2:");
    gotoxy(5, 11);
    printf("X: ");
    fgets(numStr, sizeof numStr, stdin);
    vet2.x = atof(numStr);
    gotoxy(5, 12);
    printf("Y: ");
    fgets(numStr, sizeof numStr, stdin);
    vet2.y = atof(numStr);
    gotoxy(5, 13);
    printf("Z: ");
    fgets(numStr, sizeof numStr, stdin);
    vet2.z = atof(numStr);

    result.x = vet1.x + vet2.x;
    result.y = vet1.y + vet2.y;
    result.z = vet1.z + vet2.z;

    gotoxy(3, 15);
    printf("Vetor resultante: (%.2f, %.2f, %.2f)", result.x, result.y, result.z);
    gotoxy(3, 17);
    system("pause");
    system("cls");

    return 0;
}

void limpaBuffer()
{
    while (getchar() != '\n')
        ;
}
