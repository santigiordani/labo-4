#include <modelo.h>
#include <simulacion.h>


/* Llenamos un buffer de tamaño N con valores de magnetización */
void sim_get_M(modelo *m, int N, int *buffer) {
    /*
        Hacemos N pasos MC a partir del estado actual del modelo y en cada uno
        calculamos y guardamos la magnetización en el buffer.
    */

    for (int i = 0; i < N; ++i) {

        // Damos un paso
        modelo_paso_mc(m);

        // Guardamos la magnetización
        buffer[i] = modelo_get_M(m);

    }
    
}

/* Llenamos un buffer de tamaño N con valores de energía */
void sim_get_E(modelo *m, int N, int *buffer) {
    /*
        Hacemos N pasos MC a partir del estado actual del modelo y en cada uno
        calculamos y guardamos la energía en el buffer.
    */

    for (int i = 0; i < N; ++i) {

        // Damos un paso
        modelo_paso_mc(m);

        // Guardamos la magnetización
        buffer[i] = modelo_get_E(m);

    }
    
}

/* Calculamos varios promedios luego de N pasos MC */
promedios sim_get_promedios(modelo *m, int N) {
    /*
        Hacemos N pasos MC a partir del estado actual del modelo y en cada uno
        calculamos los promedios de
            - magnetización
            - magnetización absoluta
            - energía
        y los valores de
            - susceptibilidad
            - calor específico
            - cumulante de Binder
    */

    // Variables para calcular el promedio
    double _M, _E, M_abs = 0, M2 = 0, M4 = 0, E = 0, E2 = 0;

    // Damos N pasos MC
    for (int i = 0; i < N; ++i) {

        // Damos un paso MC
        modelo_paso_mc(m);

        // Calculamos funciones de este estado
        _M = modelo_get_M(m);
        _E = modelo_get_E(m);

        // Acumulamos para el promedio
        M_abs += (_M >= 0) ? _M : - _M;
        M2 += _M * _M;
        M4 += _M * _M * _M * _M;
        E += _E;
        E2 += _E * _E;

    }

    // Promediamos
    M_abs /= N;
    M2 /= N;
    M4 /= N;
    E /= N;
    E2 /= N;

    // Calculamos otras variables
    double chi = (M2 - M_abs * M_abs) / m->T;
    double C = (E2 - E * E) / (m->T * m->T);
    double U = 1 - M4 / (3 * (M2 * M2));

    // Definimos el struct
    promedios prom = {
        M_abs,
        E,
        chi,
        C,
        U
    };

    return prom;

}