//
// Created by root on 21/11/18.
//

#ifndef CLION_CELULA_H
#define CLION_CELULA_H

typedef struct {
    int visivel;
    char valor;
    int inicial;
}Celula;

Celula CriaCelula();
void DestroiCelula(Celula* campo);
char Tiro(Celula* campo);

#endif //CLION_CELULA_H
