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

/* Inicialización de la matriz del modelo */
typedef enum {
    COLD,                           // Inicializar con todos los espines up
    HOT                             // Inicializar con todos los espines aleatorios
} start;


/* Funciones para resetear los espines */
void modelo_reset_up(modelo *m);
void modelo_reset_ran(modelo *m);

/* Funcion para resetear la temperatura */
void modelo_reset_T(modelo *m, double T);

/* Funciones para inicializar el modelo */
void modelo_init(modelo *m, start s);

/* Función para mostrar el estado en pantalla */
void modelo_print(modelo *m);
 
/* Avanzar el modelo un paso Monte Carlo */
void modelo_paso_mc(modelo *m);
 
/* Funciones para calcular magnetización y energía */
double modelo_get_M(modelo *m);
double modelo_get_E(modelo *m);


#endif // MODELO_H