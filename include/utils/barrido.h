#ifndef BARRIDO_H
#define BARRIDO_H

#include "modelo.h"
#include "simulacion.h"

/* Variables para ls función auxiliar */
#define a 0
#define b 3.3
#define Tc 2.2676


/* Función auxiliar para el barrido pesado de temperaturas */
double bar_get_T(double x, double p, double eps);

/* Función para llenar un buffer de tamaño n con datos de un barrido de temperaturas */
void bar_get_promedios(modelo *m, int N, int n, promedios *buffer, double p, double eps, int burnin);

#endif // BARRIDO_H