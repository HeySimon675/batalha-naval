//
// Created by root on 01/12/18.
//

#include "IA.h"
#include <stdlib.h>
#define TAM 5

IA* IniciaIA(){
    IA* ia = (IA*) malloc(sizeof(IA));
    ia->alvo = VetorAlvos();
    ia->n_alvos = 0;   // numero de alvos atuais
    ia->max_alvos=TAM; // tamanho inicial do vetor de alvos.

    return (ia);
}