//
// Created by root on 21/11/18.
//
#include <stdlib.h>
#include "Jogador.h"

Jogador* CadastraJogador(int id,char* tab){
    Jogador* player = (Jogador*) malloc (sizeof(Jogador));
    player->id= id;
    player->vencedor=0;
    player->frota_total = 30;
    player->tab = CriaTabuleiro(tab);
}
int FrotaAtual (Jogador* player){

}