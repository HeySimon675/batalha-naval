//
// Created by root on 21/11/18.
//

#ifndef CLION_JOGADOR_H
#define CLION_JOGADOR_H

#include "Tabuleiro.h"

typedef struct {
    int id;
    int vencedor;
    int frota_total;
    Tabuleiro* tab;
}Jogador;

Jogador* CadastraJogador(int id,char* tab);
int FrotaAtual (Jogador* player);


#endif //CLION_JOGADOR_H
