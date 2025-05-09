#ifndef BARRIDO_H
#define BARRIDO_H

#include "modelo.h"
#include "simulacion.h"

#define a 0
#define b 3.3

/* Función auxiliar para el barrido pesado de temperaturas */
double bar_get_T(double x);

/* Función para llenar un buffer de tamaño n con datos de un barrido de temperaturas */
void bar_get_promedios(modelo *m, int N, int n, promedios *buffer);

#endif // BARRIDO_H