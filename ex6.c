#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "_util.h"

struct dma
{
    int dia;
    int mes;
    int ano;
};

typedef struct dma data;

void limpaBuffer();

int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    system("cls");

    data data1, data2;
    char numStr[5];

    gotoxy(3, 3);
    printf("COMPARADOR DE DATAS");

    gotoxy(3, 5);
    printf("Data 1:");
    gotoxy(5, 6);
    printf("dia: ");
    fgets(numStr, sizeof numStr, stdin);
    data1.dia = atoi(numStr);
    gotoxy(5, 7);
    printf("mês: ");
    fgets(numStr, sizeof numStr, stdin);
    data1.mes = atoi(numStr);
    gotoxy(5, 8);
    printf("ano: ");
    fgets(numStr, sizeof numStr, stdin);
    data1.ano = atoi(numStr);

    limpaBuffer();

    gotoxy(3, 10);
    printf("Data 2:");
    gotoxy(5, 11);
    printf("dia: ");
    fgets(numStr, sizeof numStr, stdin);
    data2.dia = atoi(numStr);
    gotoxy(5, 12);
    printf("mês: ");
    fgets(numStr, sizeof numStr, stdin);
    data2.mes = atoi(numStr);
    gotoxy(5, 13);
    printf("ano: ");
    fgets(numStr, sizeof numStr, stdin);
    data2.ano = atoi(numStr);

    int dias = 0;

    for (int i = data1.ano; i <= data2.ano; i++)
    {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            month[1] = 29;
        }
        else
        {
            month[1] = 28;
        }

        if (data1.ano == data2.ano)
        {
            for (int j = data1.mes; j <= data2.mes; j++)
            {
                if (data1.mes == data2.mes)
                {
                    dias += data2.dia - data1.dia;
                    break;
                }

                if (j == data2.mes)
                {
                    dias += data2.dia;
                }
                else if (j == data1.mes)
                {
                    dias += month[data1.mes - 1] - data1.dia;
                }
                else
                {
                    dias += month[j - 1];
                }
            }

            break;
        }

        if (i == data1.ano)
        {
            for (int j = data1.mes; j <= 12; j++)
            {
                if (j == data1.mes)
                {
                    dias += month[j - 1] - data1.dia;
                }
                else
                {
                    dias += month[j - 1];
                }
            }
        }
        else if (i == data2.ano)
        {
            for (int j = 1; j <= data2.mes; j++)
            {
                if (j == data2.mes)
                {
                    dias += data2.dia;
                }
                else
                {
                    dias += month[j - 1];
                }
            }
        }
        else
        {
            if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
            {
                dias += 366;
            }
            else
            {
                dias += 365;
            }
        }
    }

    gotoxy(3, 15);
    printf("Quantidade de dias: %d", dias);
    gotoxy(3, 17);
    system("pause");

    return 0;
}

void limpaBuffer()
{
    while (getchar() != '\n')
        ;
}
