#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.h"

int main() {
    FILE* tabuleiro1 = CriaTabuleiro(1);
    FILE* tabuleiro2 = CriaTabuleiro(0);
    (void)fclose(tabuleiro1);
    (void)fclose(tabuleiro2);
    return 0;
}