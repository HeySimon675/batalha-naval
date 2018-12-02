//
// Created by root on 01/12/18.
//

#ifndef CLION_ALVO_H
#define CLION_ALVO_H

typedef struct {
    int row;
    int cow;
    int n;
    char id;
    int inicial;
}Alvos;

Alvos** VetorAlvos ();

Alvos** NovoAlvo (Alvos** vetor);

#endif //CLION_ALVO_H
