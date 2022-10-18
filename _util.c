#include "_util.h"

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
    cursorVisivel(false);
    SetConsoleTitle(nomeJanela);
    system("cls");

    gotoxy(3, 5);
    printf("%s", titulo);

    for(int i = 0; i < quantidadeMenus; i++)
    {
        gotoxy(5, i + 7);
        printf("%s", opcoes[i]);
    }

    gotoxy(3, 7);
    printf(">");
    system("pause>NUL");
}
