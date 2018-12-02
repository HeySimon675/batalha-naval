//
// Created by root on 21/11/18.
//

#ifndef CLION_CELULA_H
#define CLION_CELULA_H

typedef struct {
    int visivel;
    char valor;
    int inicial; //vai receber valores de 1-5 cada um para um sentido
    char id;
}Celula;

Celula CriaCelula();
void DestroiCelula(Celula* campo);
char Tiro(Celula* campo);

#endif //CLION_CELULA_H
