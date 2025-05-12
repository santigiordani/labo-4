#include <stdio.h>

#include <modelo.h>
#include <simulacion.h>
#include <barrido.h>


#define PASOS 10000
#define GRANDE 40
#define MEDIANO 20
#define CHICO 10


/* Cantidad a calcular */
typedef enum {
    MAGNETIZATION,
    ENERGY
} quantity;


/* Funciones para los incisos del ejercicio 1 */
void inciso_a(int n, int N, double T, char *filename, start s, quantity q);
void inciso_b(int n, int N, int temps, char *filename, start s);
void inciso_c(int n, int N, double T, char *filename, start s);

/* Función para guardar datos */
void save(int N, double *buffer, char *filename);
void save_promedios(int N, promedios *buffer, char *filename);


int main() {

    /* Con esto decidimos que inciso correr */
    const char inciso = 'c';

    switch (inciso) {
        
        case 'a':

            /* Simulaciones para el incisio a */
            inciso_a(GRANDE, PASOS, 2,      "data/a_2_cold_M.txt",  COLD, MAGNETIZATION);
            inciso_a(GRANDE, PASOS, 2,      "data/a_2_cold_E.txt",  COLD, ENERGY);
            inciso_a(GRANDE, PASOS, 3.3,    "data/a_33_cold_M.txt", COLD, MAGNETIZATION);
            inciso_a(GRANDE, PASOS, 3.3,    "data/a_33_cold_E.txt", COLD, ENERGY);
            inciso_a(GRANDE, PASOS, 2.2676, "data/a_22_cold_M.txt", COLD, MAGNETIZATION);
            inciso_a(GRANDE, PASOS, 2.2676, "data/a_22_cold_E.txt", COLD, ENERGY);
            inciso_a(GRANDE, PASOS, 2,      "data/a_2_hot_M.txt",   HOT,  MAGNETIZATION);
            inciso_a(GRANDE, PASOS, 2,      "data/a_2_hot_E.txt",   HOT,  ENERGY);
            inciso_a(GRANDE, PASOS, 3.3,    "data/a_33_hot_M.txt",  HOT,  MAGNETIZATION);
            inciso_a(GRANDE, PASOS, 3.3,    "data/a_33_hot_E.txt",  HOT,  ENERGY);
            inciso_a(GRANDE, PASOS, 2.2676, "data/a_22_hot_M.txt",  HOT,  MAGNETIZATION);
            inciso_a(GRANDE, PASOS, 2.2676, "data/a_22_hot_E.txt",  HOT,  ENERGY);
             
            break;
        
        case 'b':

            /* Simulaciones para el inciso b */
            inciso_b(GRANDE, PASOS, 100, "data/b.txt", COLD);

            break;
        
        case 'c':

            /* Simulaciones para el inciso c */
            inciso_c(GRANDE, PASOS, 2.2, "data/c_baja.txt", COLD);
            inciso_c(GRANDE, PASOS, 2.3, "data/c_alta.txt", COLD);

            break;
        
        default:

            printf("Inciso desconocido.\n");
            break;


    }

    return 0;
}


/* Función para el incisio a */
void inciso_a(int n, int N, double T, char *filename, start s, quantity q) {
    /*
        Calculamos, en función del número de pasos MC (desde 1 hasta N), los
        valores de energía y magnetización del modelo de Ising de tamaño n (con
        condiciones de borde periódicas) a temperatura T.

        Usamos MCMC sin excluír el burn-in.
    */

    // Reservamos espacio
    double buffer[N];           // Buffer para el barrido
    mtran_state mt_state;       // Estado del generador aleatorio
    short mat[n * n];           // Matriz para el modelo de Ising

    // Creamos un modelo
    modelo m = {T, n, mat, &mt_state};

    // Inicializamos el modelo
    modelo_init(&m, s);

    // Llenamos un buffer con datos de la cantidad especificada
    (q == MAGNETIZATION) ? sim_get_M(&m, N, buffer) : sim_get_E(&m, N, buffer);

    // Acumulamos las cantidades en el buffer
    for (int i = 1; i < n; ++i) {
        buffer[i] += buffer[i - 1];
    }

    // Dividimos para calcular promedios
    for (int i = 1; i <= n; ++i) {
        buffer[i] /= i;
    }

    // Guradamos los resultados
    save(N, buffer, filename);

}

/* Función para el inciso b */
void inciso_b(int n, int N, int temps, char *filename, start s) {
    /*
        Hacemos un barrido de temperaturas en [0, 3.3] con temps puntos y
        calculamos el valor medio de la magnetización absoluta y energía, la
        susceptibilidad y el calor específico. Guardamos los resultados en un
        archivo.
    */

    // Reservamos espacio
    promedios buffer[N];        // Buffer para el barrido
    mtran_state mt_state;       // Estado del generador aleatorio
    short mat[n * n];           // Matriz para el modelo de Ising

    // Creamos un modelo
    modelo m = {0, n, mat, &mt_state};

    // Inicializamos el modelo
    modelo_init(&m, s);

    // Barrido de temperaturas
    bar_get_promedios(&m, N, temps, buffer);

    // Guardamos los resultados
    save_promedios(N, buffer, filename);

}

/* Función para el incisio c */
void inciso_c(int n, int N, double T, char *filename, start s) {
    /*
        Llenamos un buffer con datos de magnetización como en el inciso 1.
        Estos datos serán usados luego para construír histogramas.
    */

    // Reservamos espacio
    double buffer[N];           // Buffer para el barrido
    mtran_state mt_state;       // Estado del generador aleatorio
    short mat[n * n];           // Matriz para el modelo de Ising

    // Creamos un modelo
    modelo m = {T, n, mat, &mt_state};

    // Inicializamos el modelo
    modelo_init(&m, s);

    // Llenamos un buffer con datos de la magnetización
    sim_get_M(&m, N, buffer);

    // Guradamos los resultados
    save(N, buffer, filename);

}


/* Función para guardar una columna de datos */
void save(int N, double *buffer, char *filename) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < N; ++i) {
        fprintf(file, "%e\n", buffer[i]);
    }
}

/* Funcion para guardar promedios del inciso b */
void save_promedios(int N, promedios *buffer, char *filename) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < N; ++i) {
        fprintf(file, "%8e %8e %8e %8e %8e\n",
            buffer[i].T,
            buffer[i].M_abs,
            buffer[i].E,
            buffer[i].chi,
            buffer[i].C
        );
    }
}