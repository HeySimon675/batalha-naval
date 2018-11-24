//
// Created by root on 21/11/18.
//
#include <stdlib.h>
#include "Game.h"

Game* NovoGame(char* tab1,char* tab2){
    //ESSA FUNÇÃO IRA CHAMAR A FUNÇÃO CRIA TABULEIRO DUAS VEZES, O PROCESSO SERA DA SEGUINTE FORMA
    //A FUNÇÃO GeraTabuleiro SERA CHAMADA DUAS VEZES, COM tab1 e tab2
    //IRA RETORNAR UM ARQUIVO TXT COM AS INFORMAÇÕES SOBRE O TABULEIRO, O ENDEREÇO DESSE ARQUIVO SERÁ PASSADO
    //PARA A FUNÇÃO CRIA TABULEIRO, QUE VAI LER ESSES ARQUIVOS E COLOCAR AS EMBARCAÇÕES NA MATRIZ DE CELULAS

    Game* game_atual = (Game*) malloc (sizeof(Game));
    game_atual->Player  = CadastraJogador(0,tab1);
    game_atual->Maquina = CadastraJogador(1,tab2);
    game_atual->fim_de_jogo=0;

}

void AtirarPlayer(Game* jogo,int id){


}