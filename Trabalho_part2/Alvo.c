//
// Created by root on 01/12/18.
//
#define TAMINICIAL 5
#include "Alvo.h"
#include <stdlib.h>

Alvos** VetorAlvos(){
    int i;
    Alvos** a = (Alvos**)malloc(TAMINICIAL* sizeof(Alvos*));
    for (i = 0; i < TAMINICIAL; i++) {
        a[i] = (Alvos*) malloc(sizeof(Alvos));
    }
        return (a);

}

