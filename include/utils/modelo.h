#ifndef MODELO_H
#define MODELO_H

#include "mtran.h"


/* Estructura representando un modelo */
typedef struct {
    double T;                       // Temperatura adimensionalizada
    int n;                          // Tamaño de la matriz
    short *mat;                     // Matriz
    mtran_state *mt_state_ptr;      // Estado del generador de números aleatorios
} modelo;


/* Funciones para resetear los espines */
void modelo_reset_up(modelo *m);
void modelo_reset_down(modelo *m);
void modelo_reset_ran(modelo *m);

/* Funcion para resetear la temperatura */
void modelo_reset_T(modelo *m, double T);

/* Funciones para inicializar el modelo */
void modelo_init_up(modelo *m, double T, int n, short *mat);
void modelo_init_down(modelo *m, double T, int n, short *mat);
void modelo_init_ran(modelo *m, double T, int n, short *mat);
 
/* Avanzar el modelo un paso Monte Carlo */
void modelo_paso_mc(modelo *m);
 
/* Funciones para calcular magnetización y energía */
double modelo_get_M(modelo *m);
double modelo_get_E(modelo *m);


#endif // MODELO_H