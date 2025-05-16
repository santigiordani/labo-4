#include <stdio.h>
#include <stdlib.h>

#include <modelo.h>
#include <simulacion.h>
#include <barrido.h>


#define PASOS 10000
#define GRANDE 40
#define MEDIANO 20
#define CHICO 10
#define BURNIN 1000


/* Cantidad a calcular */
typedef enum {
    MAGNETIZATION,
    ENERGY
} quantity;


/* Funciones para los incisos del ejercicio 1 */
void inciso_a(int n, int N, double T, char *filename, start s, quantity q);
void inciso_b(int n, int N, int temps, char *filename, start s, double p, double eps);
void inciso_c(int n, int N, double T, char *filename, start s);
void inciso_d(int n, int N, int temps, char *filename, start s, double p, double eps);
void inciso_e(int n, int N, double T, char *filename, start s, quantity q);

/* Funciones auxiliares para el inciso e */
double get_autocorr(int k, int N, double *buffer);
double get_tau(int N, double *buffer);

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
            inciso_b(CHICO  , PASOS, 100, "data/b_chico.txt",   COLD, 0.3, 0.01);
            inciso_b(MEDIANO, PASOS, 100, "data/b_mediano.txt", COLD, 0.3, 0.01);
            inciso_b(GRANDE , PASOS, 100, "data/b_grande.txt",  COLD, 0.3, 0.01);

            break;
        
        case 'c':

            /* Simulaciones para el inciso c */
            inciso_c(GRANDE, PASOS, 2, "data/c_baja.txt", HOT);
            inciso_c(GRANDE, PASOS, 2.5, "data/c_alta.txt", HOT);

            break;
        
        case 'd':

            /* Simulaciones para el inciso d */
            inciso_d(CHICO,   100 * PASOS, 10, "data/d3_chico.txt",   COLD, 0.9, 0.02);
            inciso_d(MEDIANO, 100 * PASOS, 10, "data/d3_mediano.txt", COLD, 0.9, 0.02);
            inciso_d(GRANDE,  100 * PASOS, 10, "data/d3_grande.txt",  COLD, 0.9, 0.02);

            break;
        
        case 'e':

            /* Simulaciones para el inciso e */
            inciso_e(GRANDE, PASOS, 2,      "data/e2m.txt",     COLD, MAGNETIZATION);
            inciso_e(GRANDE, PASOS, 2.2,    "data/e22m.txt",    COLD, MAGNETIZATION);
            inciso_e(GRANDE, PASOS, 2.2676, "data/e22676m.txt", COLD, MAGNETIZATION);
            inciso_e(GRANDE, PASOS, 2.5,    "data/e25m.txt",    COLD, MAGNETIZATION);
            inciso_e(GRANDE, PASOS, 3.3,    "data/e33m.txt",    COLD, MAGNETIZATION);
            inciso_e(GRANDE, PASOS, 2,      "data/e2e.txt",     COLD, ENERGY);
            inciso_e(GRANDE, PASOS, 2.2,    "data/e22e.txt",    COLD, ENERGY);
            inciso_e(GRANDE, PASOS, 2.2676, "data/e22676e.txt", COLD, ENERGY);
            inciso_e(GRANDE, PASOS, 2.5,    "data/e25e.txt",    COLD, ENERGY);
            inciso_e(GRANDE, PASOS, 3.3,    "data/e33e.txt",    COLD, ENERGY);

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
void inciso_b(int n, int N, int temps, char *filename, start s, double p, double eps) {
    /*
        Hacemos un barrido de temperaturas en [0, 3.3] con temps puntos y
        calculamos el valor medio de la magnetización absoluta y energía, la
        susceptibilidad y el calor específico. Guardamos los resultados en un
        archivo.
    */

    // Reservamos espacio
    promedios *buffer = malloc(N * sizeof(promedios));
    mtran_state mt_state;       // Estado del generador aleatorio
    short mat[n * n];           // Matriz para el modelo de Ising

    // Creamos un modelo
    modelo m = {0, n, mat, &mt_state};

    // Inicializamos el modelo
    modelo_init(&m, s);

    // Barrido de temperaturas
    bar_get_promedios(&m, N, temps, buffer, p, eps, BURNIN);

    // Guardamos los resultados
    save_promedios(temps, buffer, filename);

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

/* Función para el inciso d */
void inciso_d(int n, int N, int temps, char *filename, start s, double p, double eps) {
    /*
        El inciso d en realidad no es mas que el inciso b para 3 tamaños
        diferentes de muestra. Y guardando únicamente los cumulantes de Binder.
    */
    
    // Llamamos a la función que resuelve el inciso b
    inciso_b(n, N, temps, filename, s, p, eps);

}

/* Función para el inciso e */
void inciso_e(int n, int N, double T, char *filename, start s, quantity q) {
    /*
        Hacemos una corrida de N pasos MC en un modelo de Ising de n por n,
        calculamos la cantidad q pasada y sobre los resultados en cada paso
        calculamos el tiempo de autocorrelación.
    */

    // Reservamos espacio
    double *buffer = (double *) malloc(N * sizeof(double));
    double *autocorr = (double *) malloc((N * sizeof(double)));
    mtran_state mt_state;
    short mat[n * n];

    // Creamos un modelo
    modelo m = {T, n, mat, &mt_state};

    // Inicializamos el modelo
    modelo_init(&m, s);

    // Llenamos el buffer con la cantidad
    (q == MAGNETIZATION) ? sim_get_M(&m, N, buffer) : sim_get_E(&m, N, buffer);

    // Calculamos la autocorrelación A(k) de la cantidad:
    autocorr[0] = 1;
    for (int k = 1, last = N - 1; k < last; ++k) {
        autocorr[k] = get_autocorr(k, N, buffer);
    }

    /*
        Solo para mejorar los gráficos, una vez que la autocorrelación baja de
        0, vamos a truncarla.
    */
    int exp_domain = 1;
    for (int k = 1, last = N - 1; k < last; ++k) {
        if (autocorr[k] < 0) exp_domain = 0;
        if (!exp_domain) autocorr[k] = 0;
    }

    // Guardamos los datos
    save(N, autocorr, filename);

    // Imprimimos las autocorrelaciones
    printf("T: %8f tau_%c: %f\n", T, (q == MAGNETIZATION) ? 'M' : 'E', get_tau(N, autocorr));

}


/* Función para calcular el tiempo de autocorrelación */
double get_tau(int N, double *autocorr) {
    /*
        Calculamos el tiempo de autocorrelación a partir del buffer de
        autocorrelaciones.
    */

    double suma = 0.5;
    for (int k = 1, last = N - 1; k < last; ++k) {
        if (autocorr[k] < 0) break;
        suma += autocorr[k] * (1 - k / (double) N);
    }

    return suma;

}

/* Función para calcular la autocorrelación de los datos en un buffer */
double get_autocorr(int k, int N, double *buffer) {
    /*
        Calculamos la autocorrelación A(k) de los datos en el buffer. Por
        supuesto, k debe ser estrictamente menor a N - 1.
    */

    // Sumamos desde i = 0 hasta i = N - k
    double OiOik = 0, Oi = 0, Oi2 = 0;
    for (int i = 0, last = N - k; i < last; ++i) {
        OiOik += buffer[i] * buffer[i + k];
        Oi    += buffer[i];
        Oi2   += buffer[i] * buffer[i];
    }

    // Dividimos para obtener los promedios
    OiOik /= (N - k);
    Oi    /= (N - k);
    Oi2   /= (N - k);

    return (OiOik - Oi * Oi) / (Oi2 - Oi * Oi);

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
        fprintf(file, "%8e %8e %8e %8e %8e %8e\n",
            buffer[i].T,
            buffer[i].M_abs,
            buffer[i].E,
            buffer[i].chi,
            buffer[i].C,
            buffer[i].U
        );
    }
}