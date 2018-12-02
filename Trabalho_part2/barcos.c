//
// Created by root on 30/11/18.
//

#include "barcos.h"

Barcos* CriaBarcos (){
    int i;
    Barcos* b = (Barcos*)malloc(TIPOS * sizeof(Barcos));
    //BOMBAS
    b[0].id=0;
    b[0].barcos= (int*) malloc(10* sizeof(int));
    for(i=0; i< 10; i++){
        b[0].barcos[i] = 1;
    }
    //AVIAO
    b[1].id=1;
    b[1].barcos= (int*) malloc(5 * sizeof(int));
    for(i=0; i< 5; i++){
        b[1].barcos[i] = 4;
    }
    //SUBMARINO (DESATIVADA)
    /*
    b[2].id=2;
    b[2].barcos= (int*) malloc (5 * sizeof(int));
    for(i=0; i< 5; i++){
        b[2].barcos[i] = 4;
    }
    */
    //ESPIAO
    b[3].id=3;
    b[4].id=4;
    b[3].barcos= (int*) malloc (4* sizeof(int));
    b[4].barcos= (int*) malloc (4* sizeof(int));
    for(i=0; i< 4; i++){
        b[3].barcos[i] = 6;
        b[4].barcos[i] = 6;
    }
    //PORTA AVIOES (DESATIVADA)
    /*
    b[5].id=5;
    b[5].barcos= (int*) malloc (2* sizeof(int));
     for(i=0; i< 2; i++){
        b[5].barcos[i] = 10;
    }
    */
    return (b);
}