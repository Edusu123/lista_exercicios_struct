#include <stdbool.h>

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void cursorVisivel(bool status);
void gotoxy(int x, int y);
int geraMenu(char *nomeJanela, char *titulo, char **opcoes, int quantidadeMenus);

#endif