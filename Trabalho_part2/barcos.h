//
// Created by root on 30/11/18.
//
#include <stdio.h>
#include <stdlib.h>
#ifndef CLION_BARCOS_H
#define CLION_BARCOS_H
#define TIPOS 6

typedef struct {
    int id;
    int* barcos;
}Barcos;

Barcos* CriaBarcos ();

#endif //CLION_BARCOS_H
