#include <stdio.h>

#include "_util.h"


void main()
{
    int quantidadeMenus = 3;
    char *menu[3] = { "um", "dois", "tres" };
    
    int dec = geraMenu("Exercício 1", "Gerenciador de bandas", menu, quantidadeMenus);
}
