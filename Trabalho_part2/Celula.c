//
// Created by root on 21/11/18.
//

#include "Celula.h"
#include <stdlib.h>

Celula* CriaCelula(){
    Celula* c= (Celula*) malloc(sizeof(Celula));
    c->visivel=0;
    c->valor= '*';
    return (c);
}
void DestroiCelula(Celula* campo){
    free(campo);
    campo=NULL;
}
char Tiro(Celula* campo){
    campo->visivel=1;
    return (campo->valor);
}
