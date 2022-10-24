#include "_util.h"

#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

void cursorVisivel(bool status)
{
    if (status)
    {
        CONSOLE_CURSOR_INFO cursor = {1, TRUE};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    }
    else
    {
        CONSOLE_CURSOR_INFO cursor = {1, FALSE};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    }
}

void gotoxy(int x, int y)
{
    COORD c;

    c.X = x - 1;
    c.Y = y - 1;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int geraMenu(char *nomeJanela, char *titulo, char **opcoes, int quantidadeMenus)
{
    int posicaoAtual = 7, posicaoInicial = 7, posicaoFinal = quantidadeMenus + 6;
    cursorVisivel(false);
    SetConsoleTitle(nomeJanela);
    system("cls");

    gotoxy(3, 3);
    printf("[ESC] Sair");
    gotoxy(3, 5);
    printf("%s", titulo);

    for (int i = 0; i < quantidadeMenus; i++)
    {
        gotoxy(5, i + 7);
        printf("%s", opcoes[i]);
    }

    gotoxy(3, posicaoAtual);
    printf(">");
    system("pause>NUL");

    unsigned char input;
    bool continuaExecucao = true;

    do
    {
        int posicaoAnterior = posicaoAtual;
        input = getch();

        switch (input)
        {
        case 72: // seta para cima
            posicaoAtual -= 1;
            if (posicaoAtual < posicaoInicial)
                posicaoAtual = posicaoFinal;
            break;
        case 80: // seta para baixo
            posicaoAtual += 1;
            if (posicaoAtual > posicaoFinal)
                posicaoAtual = posicaoInicial;
            break;
        case 13:
            return posicaoAtual - 7;
        case 27: // esc
            continuaExecucao = false;
        default:
            break;
        }

        gotoxy(3, posicaoAnterior);
        printf(" ");
        gotoxy(3, posicaoAtual);
        printf(">");
    } while (continuaExecucao);

    system("cls");
    return quantidadeMenus;
}
