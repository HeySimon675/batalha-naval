//
// Created by root on 21/11/18.
//

#ifndef CLION_GAME_H
#define CLION_GAME_H

#include "Jogador.h"
#include "Alvo.h"
#include "IA.h"
#include "time.h"

typedef struct {
    Jogador* Player;
    Jogador* Maquina;
    int fim_de_jogo;
    IA* ia;
}Game;

IA* IniciaIA ();
Game* NovoGame(char* tab1,char* tab2);//recebe o txt dos tabuleiros, cria os jogadores, e inicializa os atributos de controles
void AtirarPlayer(Game* jogo,int id); //requisita as posiçoes i j onde o jogador deseja atirar e
                                        // atualiza o jogo mostrando o efeito da jogada
int VitoriasDaMaquina();        //Motra o numero de vitorias da maquina, e a porcentagem em relação a todas as partidas
int RakingPlayer();             //mostra o ranking dos melhores player, exibindo sua pontuação (que será medida pelo numero
                                //de tentativas até acertar as embarcações menos o numero de acertos da maquina)
                                //1000-(10*erros)-(10*acertosMaquina)

#endif //CLION_GAME_H
