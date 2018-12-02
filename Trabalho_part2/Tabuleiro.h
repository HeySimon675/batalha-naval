//
// Created by root on 21/11/18.
//

#ifndef CLION_TABULEIRO_H
#define CLION_TABULEIRO_H

#include "Celula.h"
#include "Gtabuleiro.h"
#include "barcos.h"
#include <stdio.h>


typedef struct {
    int linhas;
    int colunas;
    Celula** matriz_campo;
    Barcos* barcos;

}Tabuleiro;

Tabuleiro* CriaTabuleiro(char* txt);
void IncluiEmbarc (Tabuleiro* tab, FILE* tabfile);
void DestroiTabuleiro(Tabuleiro* tab);

void IncluiBomba (Tabuleiro* tab,int i, int j, char n);

void IncluiAviao (Tabuleiro* tab,int i  , int j, int pos);

void IncluiSubmarino (Tabuleiro* tab, int i, int j, char* pos);

void IncluiEspiao (Tabuleiro* tab, int i, int j, int pos,char id);

void IncluiPAviao (Tabuleiro* tab, int i, int j, int pos);

void PrintaTabNovo (Tabuleiro *tab);

void PrintaTabuleiro (Celula** matriz, int row);



#endif //CLION_TABULEIRO_H
