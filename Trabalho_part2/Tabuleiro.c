//
// Created by root on 21/11/18.
//
#include <stdlib.h>
#include "Tabuleiro.h"
#define ROW 20
#define COW 20
extern int i_inicial, i_final, j_inicial, j_final;

void IncluiBomba (Tabuleiro* tab,int i, int j) {
    tab->matriz_campo[i][j].valor='0';
}
void IncluiAviao (Tabuleiro* tab,int i, int j, int pos){
    extern int i_inicial, i_final, j_inicial, j_final;
    tab->matriz_campo[i][j].inicial=1;
    switch (pos){
        case 0:
            j_inicial=j-1;
            i_inicial=i-1;
            i_final=i_inicial+3;
            j_final=j_inicial+2;
            break;
    }
}

void IncluiSubmarino (Tabuleiro* tab, int i, int j, int pos){

}

void IncluiEspiao (Tabuleiro* tab, int i, int j, int pos,char id){

}

void IncluiPAviao (Tabuleiro* tab, int i, int j, int pos){


}

void IncluiEmbarc (Tabuleiro* tab, FILE* tabfile){
    char n,id,pos,i[2],j[2];
    while (fscanf(tabfile,"%[^ ] %[^ ] %[^ ] %[^ ] %[^\n]\n",&n,&id,&pos,i,j) != EOF){
        if(id=='0') {
            IncluiBomba(tab, (atoi(i)), atoi(j));
        }else if (id=='1'){
            IncluiAviao(tab,atoi(i),atoi(j),atoi(&pos));
        }else if (id=='2'){
            IncluiSubmarino(tab,atoi(i),atoi(j),atoi(&pos));
        }else if (id=='3' || id=='4'){
            IncluiEspiao(tab, atoi(i),atoi(j),atoi(&pos),id);
        }else
            IncluiPAviao(tab,atoi(i),atoi(j),atoi(&pos));
    }
}

void PreencheTabuleiro(Tabuleiro* tab){
    int i, j;
    for(i=0;i<ROW;i++){
        for (j = 0; j < COW; j++) {
            tab->matriz_campo[i][j] = CriaCelula();
        }
    }
}

Tabuleiro* CriaTabuleiro(char* txt){
    int i;
    FILE* tabfile;
    Tabuleiro* tab = (Tabuleiro*) malloc((sizeof(Tabuleiro)));
    tab->linhas=ROW;
    tab->colunas=COW;
    tab->matriz_campo = (Celula**) malloc(tab->linhas* sizeof(Celula*));
    for (i = 0; i < COW; i++) {
        tab->matriz_campo[i]= (Celula*) malloc(ROW* sizeof(Celula));
    }
    GeraTabuleiro(txt);
    tabfile = fopen(txt,"r");
    PreencheTabuleiro(tab);
    IncluiEmbarc(tab,tabfile);
}


void DestroiTabuleiro(Tabuleiro* tab){

}