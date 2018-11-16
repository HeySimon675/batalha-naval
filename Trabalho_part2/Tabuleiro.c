//
// Created by root on 14/11/18.
//
/*=========GERADOR DE TABULEIRO==========*/
#include "tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Declaração de variaveis externas:

int POS; //A Variavel POS será usava pra guardar a posição das embarcações

//Preenche a matriz com *
void Preenche_Matriz(char m[20][20]){
    int i,j;
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            m[i][j] ='*';
        }
    }
}

//Troca valores de largura e altura
void Posicao (int *largura, int *altura){
    int aux;
    aux = *largura;
    *largura = *altura;
    *altura = aux;
}


//COLOCA EMBARCAÇÃO DO TIPO ESPIAO NA MATRIZ
void Coloca_Espiao (char m[20][20], int i_inicial,int j_inicial,int i_final,int j_final,char id){
    extern int POS;
    int i,j;
    switch (POS){
        case 0: //horizontal direcionado para a direita
            i=i_inicial+1;
            for(j=j_inicial;j < j_final; j++){
                m[i][j]=id;
            }
            m[i_inicial][j_inicial]=id;
            m[i_inicial+2][j_inicial]=id;
            break;
        case 1: //vertical para cima
            j=j_inicial+1;
            for (i = i_inicial; i < i_final; i++) {
                m[i][j] = id;
            }
            m[i-1][j_inicial] = id;     //coloca as "turbinas" da embarcação
            m[i-1][j_inicial+2] = id;
            break;
        case 2:  //horizontal direcionado para a esquerda
            i=i_inicial+1;
            for(j=j_inicial;j < j_final; j++){
                m[i][j]=id;
            }
            m[i_inicial][j_final-1]=id;
            m[i_inicial+2][j_final-1]=id;
            break;
        case 3:     //vertical para baixo
            j=j_inicial+1;
            for (i = i_inicial; i < i_final; i++) {
                m[i][j] = id;
            }
            m[i_inicial][j_inicial] = id;     //coloca as "turbinas" da embarcação
            m[i_inicial][j_inicial+2] = id;
            break;
    }

}
//COLOCA EMBARCAÇÕES DO TIPO AVIÃO
void Coloca_Aviao (char m[20][20], int i_inicial,int j_inicial,int i_final,int j_final){
    extern int POS;
    int i,j;
    char id='1';
    switch (POS) {
        case 0:
            j = j_inicial + 1;
            for (i = i_inicial; i < i_final; i++)
                m[i][j] = id;
            m[i_inicial + 1][j_inicial] = id;
            break;
        case 1:
            i = i_inicial;
            m[i_inicial + 1][j_inicial + 1] = id;
            for (j = j_inicial; j < j_final; j++)
                m[i][j] = id;   //coloca a "cauda" do avião
            break;
        case 2 :
            j = j_inicial;
            for (i = i_inicial; i < i_final; i++)
                m[i][j] = id;
            m[i_inicial + 1][j_inicial+1] = id;
            break;
        case 3:
            i = i_inicial+1;
            m[i_inicial][j_inicial + 1] = id;
            for (j = j_inicial; j < j_final; j++)
                m[i][j] = id;   //coloca a "cauda" do avião
            break;
    }
}
//ENCONTRA UMA POSIÇÃO VALIDA E ALOCA AS EMBARCAÇÕES
int Posicionadora (char m[20][20], int largura,int altura, char id){
    int i_final,j_final,i,j, i_inicial, j_inicial;
    i_inicial = rand() % (20 - altura);     //sorteia uma posição, limitada pelo tamanho da embarcação
    j_inicial = rand() % (20 - largura);
    i_final = i_inicial + altura;
    j_final = j_inicial + largura;
    for (i = i_inicial; i < i_final; i++) {
        for (j = j_inicial; j < j_final; j++) {
            if (m[i][j] != '*')
                return (0);     //retorna zero se as posições larguraXaltura estiverem ocupadas
        }
    }
    if ((id=='3') || (id=='4'))     //para espião
        Coloca_Espiao(m,i_inicial,j_inicial,i_final,j_final,id);
    else if (id=='1'){              //para avião
        Coloca_Aviao(m,i_inicial,j_inicial,i_final,j_final);
    }else if(id=='0')               //para bomba
        m[i_inicial][j_inicial]=id;
    else {                          // para Porta avioes e Submarino
        for (i = i_inicial; i < i_final; i++) {
            for (j = j_inicial; j < j_final; j++)
                m[i][j] = id;
        }
    }
    return (1); //retorna 1 se encontrou a posição valida
}
//Solicita n Porta aviões
void Porta_Avioes(char m[20][20], int n) {
    extern int POS;
    int i, erro = 0;
    char id = '5';
    int largura = 5;
    int altura = 2;
    for (i = 0; i < n; i++) {

        erro=0;
        POS = rand() % 4;
        if (POS%2)
            Posicao(&largura,&altura);
        while (!erro) {     //Continua até conseguir posicionar a embarcação
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}
//Solicita n Submarinos
void Submarino(char m[20][20], int n, char id) {
    extern int POS;
    int  i, erro = 0;
    int largura = 4;
    int altura = 1;
    for (i = 0; i < n; i++) {
        erro=0;
        POS = rand() % 4;
        if (POS%2)
            Posicao(&largura,&altura);
        while (!erro) {
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}
//Solicita n Espiões de identificador id :3
void Espiao (char m[20][20], int n, char id) {
    extern int POS;
    int largura ,altura;
    int  i, erro = 0;
    for (i = 0; i < n; i++) {
        largura = 4;
        altura = 3;
        erro = 0;
        POS = rand() % 4; //guarda a posição na variavel externa
        if (POS%2)
            Posicao(&largura,&altura);
        while (!erro) {
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}
//Solicita n aviões
void Aviao (char m[20][20], int n,char id){
    extern int POS;
    int largura ,altura;
    int  i, erro = 0;
    for (i = 0; i < n; i++) {
        largura = 2;
        altura = 3;
        erro = 0;
        POS = rand() % 4;    //guarda a posição da figura em uma variavel externa
        if (POS%2)
            Posicao(&largura,&altura);
        while (!erro) {
            erro  = Posicionadora(m, largura, altura, id);
        }
    }
}
//Solicita n bombas
void Bomba (char m[20][20], int n){
    int i,erro;
    for (i = 0; i < n; i++) {
        erro=0;
        while (!erro){
            erro=Posicionadora(m,1,1,'0');
        }
    }
}
//Exibe o tabuleiro com suas respectivas coordenadas :)
void Printa_Matriz(char m[20][20]){
    int i,largura=20,altura=20;
    char j;
    printf("   ");
    for(j='A';j<'A'+largura;j++)
        printf("%c ",j);
    printf("\n");
    for(i=0;i<altura;i++){
        printf("%2d ",i);
        for(j=0;j<largura;j++)
            printf("%c ",m[i][j]);
        printf("\n");
    }
}

FILE * CreateTab(char* nome_arquivo){

    FILE *tabuleiro = fopen(tabuleiro, "w");
    if(tabuleiro != NULL)
        return (-1);
        //não foi possivel criar o arquivo
}

int main() {
    char matriz[20][20];
    char* Nome_tabuleiro; //nome que será definido pela variavel modo.
    
    FILE* tab = CreateTab(Nome_tabuleiro);
    srand(time(NULL));
    Preenche_Matriz(matriz);
    Porta_Avioes(matriz,2);
    Espiao(matriz,4,'3');
    Espiao(matriz,4,'4');
    Aviao(matriz,5,'1');
    Submarino(matriz,5,'2');
    Bomba(matriz,10);
    Printa_Matriz(matriz);  //substituir por impressão em arquivo .txt
    return 0;
}
