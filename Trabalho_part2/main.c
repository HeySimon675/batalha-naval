#include <stdio.h>
#include <stdlib.h>
#include "Gtabuleiro.h"
#include "Game.h"

#define TAB_PLAYER "tabuleiro1.txt"
#define TAB_MAQUINA "tabuleiro2.txt"

#define  PLAYER_ID 0
#define  MAQUINA_ID 1

#include "Game.h"


int main() {

    Game* jogo = NovoGame(TAB_PLAYER,TAB_MAQUINA);

    do{

    }while (!jogo->fim_de_jogo);
        AtirarPlayer(jogo,PLAYER_ID);
        AtirarPlayer(jogo,MAQUINA_ID);

    //FILE* tabuleiro1 = CriaTabuleiro;
    //fclose(tabuleiro1);
    return 0;
}
