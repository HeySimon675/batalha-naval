//
// Created by root on 21/11/18.
//
#include <stdlib.h>
#include "Tabuleiro.h"
#define ROW 20
#define COW 20


void PreencheTabuleiro(Tabuleiro* tab){
    int i, j;
    for(i=0;i<ROW;i++){
        for (j = 0; j < COW; j++) {
            tab->matriz_campo[i][j] = CriaCelula;

        }
    }

}

Tabuleiro* CriaTabuleiro(){
    int i,j;
    Tabuleiro* tab = (Tabuleiro*) malloc((sizeof(Tabuleiro)));
    tab->linhas=ROW;
    tab->colunas=COW;
    tab->matriz_campo = (Celula**) malloc(tab->linhas* sizeof(Celula*));
    for (i = 0; i < COW; i++) {
        tab->matriz_campo[i]= (Celula*) malloc(ROW* sizeof(Celula));
    }
    PreencheTabuleiro(tab);
}


void DestroiTabuleiro(Tabuleiro* tab){

}