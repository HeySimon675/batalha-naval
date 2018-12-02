// Created by root on 21/11/18.
#include <stdlib.h>
#include "Tabuleiro.h"
#define ROW 20
#define COW 20
#define NORTE 0
#define SUL 1
#define LESTE 2
#define OESTE 3


void IncluiBomba (Tabuleiro* tab,int i, int j, char n) {
    tab->matriz_campo[i][j-1].valor='0'; //(j-1) pois não encontrei o erro onde a bomba ficava sempre uma coluna a frente, o que não fazia nenhum sentido
    tab->matriz_campo[i][j-1].id=n;
}
void IncluiAviao (Tabuleiro* tab,int i, int j, int pos){
    int x, y;
    tab->matriz_campo[i][j].inicial=(pos+1);
    switch (pos){
        case LESTE: //LESTE
            y=j;
            for(x=i-1; x<(i+2) ; x++){  //(x+2) esta definindo o limite de altura do aviao
                tab->matriz_campo[x][y].valor='1'; // 1 é o id do aviao
            }
            tab->matriz_campo[i][j-1].valor='1'; //coloca a cauda do avião, que esta à esquerda da posição inicial
            break;
        case OESTE: // OESTE
            y=j;
            for(x=i-1; x<(i+2) ; x++){  //(x+2) esta definindo o limite de altura do aviao
                tab->matriz_campo[x][y].valor='1'; // 1 é o id do aviao
            }
            tab->matriz_campo[i][j+1].valor='1'; //coloca a cauda do avião, que esta à direita da posição inicial
            break;

        case NORTE: //NORTE
            x=i;
            for(y=(j-1);y<(j+2);y++){
                tab->matriz_campo[x][y].valor='1'; // 1 é o id do aviao
            }
            tab->matriz_campo[i+1][j].valor='1'; //coloca a cauda do avião, que esta à abaixo da posição inicial
            break;

        case SUL: //SUL
            x=i;
            for(y=(j-1);y<(j+2);y++){
                tab->matriz_campo[x][y].valor='1'; // 1 é o id do aviao
            }
            tab->matriz_campo[i-1][j].valor='1'; //coloca a cauda do avião, que esta à acima da posição inicial
            break;
    }
}

void IncluiSubmarino (Tabuleiro* tab, int i, int j, char* pos){
    int x, y ;
    tab->matriz_campo[i][j].inicial=(atoi(pos)+1);
    switch (*pos){
        case '2': //LESTE
            for(y=j; y<(j+4) ; y++){  //(y+4) esta definindo o limite de largura do submarino
                tab->matriz_campo[i][y].valor='2'; // 2 é o id do submarino
            }
            break;
        case '3': // OESTE
            for(y=(j); y>(j-4) ; y--){  //(j-3) pois o ponto inicial é na ponta direita, (y+1) esta definindo o limite de largura do submarino
                tab->matriz_campo[i][y].valor='2'; // 2 é o id do submarino
            }
            break;

        case '0': //NORTE
            for(x=i; x<(i+4) ; x++){  //(i+4) esta definindo o limite de altura do submarino
                tab->matriz_campo[x][j].valor='2'; // 2 é o id do submarino
            }
            break;
        case '1': //SUL
            for(x=(i); x>(i-4) ; x--){  //(i-3) pois o ponto inicial é na ponta embaixo, (x+1) esta definindo o limite de altura do submarino
                tab->matriz_campo[x][j].valor='2'; // 2 é o id do submarino
            }
            break;
    }
}

void IncluiEspiao (Tabuleiro* tab, int i, int j, int pos,char id){
    int x,y;
    tab->matriz_campo[i][j].inicial=(pos+1);
    switch (pos){
        case LESTE: //LESTE
            for(y=j; y<(j+4) ; y++){  //(y+4) esta definindo o limite de largura do espiao
                tab->matriz_campo[i][y].valor=id;
            }
            tab->matriz_campo[i-1][j].valor=id;
            tab->matriz_campo[i+1][j].valor=id;
            break;
        case OESTE: // OESTE
            for(y=(j-3); y<(j+1) ; y++){  //(j-3) pois o ponto inicial é na ponta direita, (y+1) esta definindo o limite de largura do espiao
                tab->matriz_campo[i][y].valor=id ;
            }
            tab->matriz_campo[i+1][j].valor=id ;
            tab->matriz_campo[i-1][j].valor=id ;
            break;
        case SUL:
            for(x=i; x<(i+4) ; x++){  //(i+4) esta definindo o limite de altura do submarino
                tab->matriz_campo[x][j].valor=id; // 2 é o id do submarino
            }
            tab->matriz_campo[i][j-1].valor=id ;
            tab->matriz_campo[i][j+1].valor=id ;
            break;
        case NORTE:
            for(x=(i-3); x<(i+1) ; x++){  //(i-3) pois o ponto inicial é na ponta embaixo, (x+1) esta definindo o limite de altura do espiao
                tab->matriz_campo[x][j].valor=id;
            }
            tab->matriz_campo[i][j-1].valor=id ;
            tab->matriz_campo[i][j+1].valor=id ;
            break;
    }
}

void IncluiPAviao (Tabuleiro* tab, int i, int j, int pos){
    int x, y ;
    tab->matriz_campo[i][j].inicial=(pos+1);
    switch (pos){
        case LESTE: //LESTE

            for(x=i;x<(i+2);x++) { // (i+2) é o limite da altura do porta avioes no sentido leste
                for (y = j; y < (j + 5); y++) {  //(j+5) esta definindo o limite de largura do porta avioes
                    tab->matriz_campo[x][y].valor = '5'; // 5 é o id do porta avioes
                }
            }
            break;
        case OESTE: // OESTE
            for (x=(i-1); x< (i+1) ; x++) { //(i+1) é o limite da altura do porta avioes
                 for (y = (j - 4); y < (j + 1); y++) {  //(j-4) pois o ponto inicial é na ponta direita, (j+1) esta definindo o limite de altura do porta avioes
                    tab->matriz_campo[x][y].valor = '5';
                }
            }
            break;

        case NORTE: //NORTE
            for (x=i; x< (i+5) ; x++) { //(i+5) é o limite da altura do porta avioes quando esta na vertical
                for (y = j; y < (j + 2); y++) {  //(j+2) esta definindo o limite de largura do porta avioes
                    tab->matriz_campo[x][y].valor = '5';
                }
            }
            break;
        case SUL: //SUL
            for (x=(i-4); x< (i+1) ; x++) { //(i-4), pois o ponto inicial está na ultima linha, (i+1) é o limite da altura do porta avioes
                for (y = (j-1); y < (j + 1); y++) {  //(j-1) pois o ponto inicial é na ponta direita, (j+1) esta definindo o limite de altura do porta avioes
                    tab->matriz_campo[x][y].valor = '5';
                }
            }
            break;
    }

}

void IncluiEmbarc (Tabuleiro* tab, FILE* tabfile){
    char n,id,pos[2],i[3],j[3];
    while (fscanf(tabfile,"%[^ ] %[^ ] %[^ ] %[^ ] %[^\n]\n",&n,&id,pos,i,j) != EOF){
        if(id=='0') {
            IncluiBomba(tab, (atoi(i)), atoi(j),n);
        }else if (id=='1'){
            IncluiAviao(tab,atoi(i),atoi(j),atoi(pos));
        }else if (id=='2'){
            IncluiSubmarino(tab,atoi(i),atoi(j),(pos));
        }else if (id=='3' || id=='4'){
            IncluiEspiao(tab, atoi(i),atoi(j),atoi(pos),id);
        }else
            IncluiPAviao(tab,atoi(i),atoi(j),atoi(pos));
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
    tab->barcos = CriaBarcos();
    GeraTabuleiro(txt);
    tabfile = fopen(txt,"r");
    PreencheTabuleiro(tab);
    IncluiEmbarc(tab,tabfile);
    PrintaTabNovo(tab);
    return (tab);
}

void PrintaTabNovo (Tabuleiro *tab){
    int i;
    char j;
    printf("   ");
    for(j='A';j<'A'+ tab->colunas;j++) // printa o cabeçalho da matriz de A até T
        printf("%c ",j);
    printf("\n");
    for(i=0;i< tab->linhas ;i++){
        printf("%2d ",i);
        for(j=0;j< tab->colunas ;j++)
            printf("%c ",tab->matriz_campo[i][j].valor);
        printf("\n");
    }
}

void PrintaTabuleiro (Celula** matriz, int row){
    int i;
    char j;
    printf("   ");
    for(j='A';j<'A'+ COW;j++) // printa o cabeçalho da matriz de A até T
        printf("%c ",j);
    printf("\n");
    for(i=0;i< ROW ;i++){
        printf("%2d ",i);
        for(j=0;j< COW ;j++)
            if(matriz[i][j].visivel)
                printf("%c ",matriz[i][j].valor);
            else
                printf("* ");
        printf("\n");
    }
}

void DestroiTabuleiro(Tabuleiro* tab){
    //Desaloca o tabuleiro, sera chamada assim que um jogo acabar
}