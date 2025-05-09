#ifndef MODELO_H
#define MODELO_H

#include "mtran.h"

/* Estructura representando un modelo */
typedef struct {
    double T;
    int n;
    short *mat;
    mtran_state *mt_state_ptr;
} modelo;

#endif // MODELO_H