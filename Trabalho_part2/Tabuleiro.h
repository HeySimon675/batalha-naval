//
// Created by root on 14/11/18.
//

#ifndef TRABALHO_2_TABULEIRO_H
#define TRABALHO_2_TABULEIRO_H

#include <stdio.h>

//Troca os valores largura x altura para objeto na vertical ou horizontal
void Posicao (int *largura, int *altura);

//COLOCA EMBARCAÇÕES DO TIPO ESPIAO
void Coloca_Espiao (char m[20][20], int i_inicial,int j_inicial,int i_final,int j_final,char id);

//COLOCA EMBARCAÇÕES DO TIPO AVIÃO
void Coloca_Aviao (char m[20][20], int i_inicial,int j_inicial,int i_final,int j_final);

//ENCONTRA UMA POSIÇÃO VALIDA E ALOCA AS EMBARCAÇÕES
int Posicionadora (char m[20][20], int largura,int altura, char id);

//Solicita n Porta aviões
void Porta_Avioes(char m[20][20], int n);

//Solicita n Submarinos
void Submarino(char m[20][20], int n, char id);

//Solicita n Espiões de identificador id
void Espiao (char m[20][20], int n, char id);

//Solicita n aviões
void Aviao (char m[20][20], int n,char id);

//Solicita n bombas
void Bomba (char m[20][20], int n);

//Exibe o tabuleiro com suas respectivas coordenadas
void Printa_Matriz(char m[20][20]);

//Cria um tabuleiro .txt
FILE* CriaTabuleiro (int modo);                      // 0 para maquina 1 para player














#endif //TRABALHO_2_TABULEIRO_H
