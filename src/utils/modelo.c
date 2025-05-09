#include <math.h>
#include <modelo.h>


/*

    Es importante destacar que el usuario es responsable de reservar en memoria
    el espacio para un struct modelo, para la matriz de short de este modelo,
    y para el struct mtran_state. Esto es principalmente por dos razones:
        - Porque permite que la matriz se almacene en el stack, que es mas
          rápido, y tiene mas chances de entrar en el cache.
        - Porque ceder esta responsabilidad al usuario evita las fugas de
          memoria.

    Entonces, un uso típico del modelo sería:
    
    // Definir los parámetros
    double T = 0;
    int n = 10;

    // Reservar espacio
    mtran_state mt_state;
    short mat[n * n];
    modelo m;

    // Inicializar el modelo
    modelo_init_up(m, T, n, mat);

*/


/* Inicializamos el modelo m con todos los espines up */
void modelo_init_up(modelo m, double T, int n, short *mat) {
    /*
        Inicilaizamos el modelo m con todos los espines up
    */

    // Inicializamos la semilla
    mtran_set(m.mt_state_ptr, 5489UL);
    
    // Guardamos los atributos
    m.T = T;
    m.n = n;
    m.mat = mat;

    // Llenamos la matriz de espines up
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(m.mat + n * i + j) = (short) 1;
        }
    }

}

/* Inicializamos el modelo m con todos los espines down */
void modelo_init_down(modelo m, double T, int n, short *mat) {
    /*
        Inicilaizamos el modelo m con todos los espines down
    */

    // Inicializamos la semilla
    mtran_set(m.mt_state_ptr, 5489UL);
    
    // Guardamos los atributos
    m.T = T;
    m.n = n;
    m.mat = mat;

    // Llenamos la matriz de espines up
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(m.mat + n * i + j) = (short) -1;
        }
    }

}

/* Inicializamos el modelo m con todos los espines aleatorios */
void modelo_init_ran(modelo m, double T, int n, short *mat) {
    /*
        Inicilaizamos el modelo m con todos los espines aleatorios
    */

    // Inicializamos la semilla
    mtran_set(m.mt_state_ptr, 5489UL);
    
    // Guardamos los atributos
    m.T = T;
    m.n = n;
    m.mat = mat;

    // Llenamos la matriz de espines up
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(m.mat + n * i + j) = (short) ((mtran(m.mt_state_ptr) > .5) ? 1 : -1);
        }
    }

}

/* Avanzar el modelo un paso Monte Carlo */
void modelo_paso_mc(modelo m) {
    /*
        Avanzamos un paso Monte Carlo el modelo m de acuerdo con el método
        Metrópolis.
    */

    // Seleccionamos un par de índices
    int i = (int) (m.n * mtran(m.mt_state_ptr));
    int j = (int) (m.n * mtran(m.mt_state_ptr));
    
    // Calculamos la diferencia de energía
    double dE = (double) 2 * *(m.mat + m.n * i + j) * (
        *(m.mat + m.n * i + ((j + 1) % m.n)) +
        *(m.mat + m.n * i + ((j - 1) % m.n)) +
        *(m.mat + m.n * ((i + 1) % m.n) + j) +
        *(m.mat + m.n * ((i - 1) % m.n) + j)
    );

    // Calculamos la probabilidad de aceptar el flip
    double p = (m.T == 0) ? 1 : exp(- dE / m.T);

    // Hacemos o no el flip
    if (mtran(m.mt_state_ptr) < p) *(m.mat + m.n * i + j) *= -1;

}

/* Calculamos la magnetización */
double modelo_get_M(modelo m) {
    /*
        Calculamos la magnetización del modelo en el estado actual.
    */

    int sum = 0;
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) {
            sum += (int) *(m.mat + m.n * i + j);
        }
    }

    return (double) sum;

}

/* Calculamos la energía */
double modelo_get_E(modelo m) {
    /*
        Calculamos la energía del modelo en el estado actual.
    */

    int sum = 0;
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) {

            // Sumamos solo los vecinos de arriba y de la derecha
            sum += (int) *(m.mat + m.n * i + j) * (
                *(m.mat + m.n * ((i + 1) % m.n) + j) + 
                *(m.mat + m.n * i + ((j + 1) % m.n))
            );

        }
    } 

    return (double) sum;

}