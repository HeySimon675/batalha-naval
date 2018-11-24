//
// Created by root on 21/11/18.
//

#ifndef CLION_TABULEIRO_H
#define CLION_TABULEIRO_H

#include "Celula.h"
#include "Gtabuleiro.h"
#include <stdio.h>
//#include "Embarc.h"

typedef struct {
    int linhas;
    int colunas;
    Celula** matriz_campo;
}Tabuleiro;

Tabuleiro* CriaTabuleiro(char* txt);
void IncluiEmbarc (Tabuleiro* tab, FILE* tabfile);
void DestroiTabuleiro(Tabuleiro* tab);


//FUNÇÕES DA BIBLIOTECA EMBARC, QUE POR ALGUM CARALHO DE MOTIVO NAO TA FUNCIONANDO

void IncluiBomba (Tabuleiro* tab,int i, int j);

void IncluiAviao (Tabuleiro* tab,int i  , int j, int pos);

void IncluiSubmarino (Tabuleiro* tab, int i, int j, int pos);

void IncluiEspiao (Tabuleiro* tab, int i, int j, int pos,char id);

void IncluiPAviao (Tabuleiro* tab, int i, int j, int pos);



#endif //CLION_TABULEIRO_H
