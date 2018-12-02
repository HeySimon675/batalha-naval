//
// Created by root on 01/12/18.
//

#ifndef CLION_IA_H
#define CLION_IA_H

#include "Alvo.h"
typedef struct {
    Alvos** alvo;
    int n_alvos;
    int max_alvos;
}IA;

IA* IniciaIA();
#endif //CLION_IA_H
