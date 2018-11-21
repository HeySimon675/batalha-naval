//
// Created by root on 21/11/18.
//

#ifndef CLION_TABULEIRO_H
#define CLION_TABULEIRO_H

#include "Celula.h"
#include <stdio.h>


typedef struct {
    int linhas;
    int colunas;
    Celula** matriz_campo;
}Tabuleiro;

Tabuleiro* CriaTabuleiro();
void DestroiTabuleiro(Tabuleiro* tab);

#endif //CLION_TABULEIRO_H
