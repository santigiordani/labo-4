#include <math.h>
#include <stdio.h>
#include <modelo.h>


/*

    El usuario es responsable de reservar espacio en memoria para:
        - El estado del generador de números aleatorios
        - La matriz para el modelo
        - El struct modelo
    
    Esto es principalmente por 2 razones:
        - Para evitar memory leaks
        - Para que todo quede en el stack, y posiblemente en el cache
    
    Un uso típico del modelo sería:
    
    // Definir los parámetros
    double T = 0;
    int n = 10;

    // Reservar espacio
    mtran_state mt_state;
    short mat[n * n];

    // Crear el modelo
    modelo m = {T, n, mat, &mt_state};

    // Inicializar el modelo
    modelo_init(&m, COLD);

*/


/* Reseteamos la matriz con todos los espines up */
void modelo_reset_up(modelo *m) {
    /*
        Reseteamos la matriz del modelo m con todos los espines up
    */

    for (int i = 0; i < m->n; ++i) {
        for (int j = 0; j < m->n; ++j) {
            *(m->mat + m->n * i + j) = (short) 1;
        }
    }

}

/* Reseteamos la matriz con todos los espines aleatorios */
void modelo_reset_ran(modelo *m) {
    /*
        Reseteamos la matriz del modelo m con todos los espines aleatorios
        uniformemente distribuídos.
    */

    for (int i = 0; i < m->n; ++i) {
        for (int j = 0; j < m->n; ++j) {
            *(m->mat + m->n * i + j) = (short) ((mtran(m->mt_state_ptr) > .5) ? 1 : -1);
        }
    }

}

/* Inicializamos el modelo m */
void modelo_init(modelo *m, start s) {
    /*
        Inicilaizamos el modelo m con todos los espines aleatorios
        uniformemente distribuídos.
    */

    // Inicializamos la semilla
    mtran_set(m->mt_state_ptr, 5489UL);
    
    // Setteamos todos los espines aleatorios
    (s == COLD) ? modelo_reset_up(m) : modelo_reset_ran(m);

}

/* Reseteamos la temperatura */
void modelo_reset_T(modelo *m, double T) {
    /*
        Reseteamos la temperatura del modelo.
    */

    m->T = T;

}

/* Mostramos en pantalla el estado */
void modelo_print(modelo *m) {
    /*
        Mostramos en pantalla los parámetros del modelo y el estado de la
        matriz de espines.
    */

    printf("Temperatura: %f\n", m->T);
    printf("Tamaño:      %d\n", m->n);
    printf("Espines:\n");
    for (int i = 0; i < m->n; ++i) {
        for (int j = 0; j < m->n; ++j) {
            printf("%s ", (*(m->mat + i * m->n + j) == 1) ? "##" : "  ");
        }
        printf("\n");
    }

}

/* Avanzar el modelo un paso Monte Carlo */
void modelo_paso_mc(modelo *m) {
    /*
        Avanzamos un paso Monte Carlo el modelo m de acuerdo con el método
        Metrópolis.
    */

    // Un paso MC consta de m.n * m.n intentos de flip
    for (int n2 = m->n * m->n, k = 0; k < n2; ++k) {
    
        // Seleccionamos un par de índices
        int i = (int) (m->n * mtran(m->mt_state_ptr));
        int j = (int) (m->n * mtran(m->mt_state_ptr));
    
        // Calculamos la diferencia de energía
        double dE = (double) 2 * *(m->mat + m->n * i + j) * (
            *(m->mat + m->n * i + ((j + 1) % m->n)) +
            *(m->mat + m->n * i + ((j + m->n - 1) % m->n)) +
            *(m->mat + m->n * ((i + 1) % m->n) + j) +
            *(m->mat + m->n * ((i + m->n - 1) % m->n) + j)
        );

        // Hacemos o no el flip
        if (- m->T * log(mtran(m->mt_state_ptr)) > dE) *(m->mat + m->n * i + j) *= -1;

    }

}

/* Calculamos la magnetización */
double modelo_get_M(modelo *m) {
    /*
        Calculamos la magnetización del modelo en el estado actual.
    */

    int sum = 0;
    for (int i = 0; i < m->n; ++i) {
        for (int j = 0; j < m->n; ++j) {
            sum += (int) *(m->mat + m->n * i + j);
        }
    }

    return (double) sum;

}

/* Calculamos la energía */
double modelo_get_E(modelo *m) {
    /*
        Calculamos la energía del modelo en el estado actual.
    */

    int sum = 0;
    for (int i = 0; i < m->n; ++i) {
        for (int j = 0; j < m->n; ++j) {

            // Sumamos solo los vecinos de abajo y de la derecha
            sum += (int) *(m->mat + m->n * i + j) * (
                *(m->mat + m->n * ((i + 1) % m->n) + j) + 
                *(m->mat + m->n * i + ((j + 1) % m->n))
            );

        }
    } 

    return - (double) sum;

}