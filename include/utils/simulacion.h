#ifndef SIMULACION_H
#define SIMULACION_H

#include "modelo.h"


/* Estructura agrupando un conjunto de promedios */
typedef struct {
    double T;           // Temperatura
    double M_abs;       // Valor absoluto de la magnetización
    double E;           // Energía
    double chi;         // Susceptibilidad
    double C;           // Calor específico
    double U;           // Cumulante de Binder
} promedios;


/* Funciones para resetear los espines del modelo */
void sim_reset_up(modelo *m);
void sim_reset_down(modelo *m);
void sim_reset_ran(modelo *m);

/* Funciones para llenar un buffer con valores de magnetización y energía */
void sim_get_M(modelo *m, int N, double *buffer);
void sim_get_E(modelo *m, int N, double *buffer);

/* Funcion para calcular promedios a lo largo de N pasos MC */
promedios sim_get_promedios(modelo *m, int N, int burnin);
 

#endif // SIMULACION_H