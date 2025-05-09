#include <modelo.h>
#include <simulacion.h>
#include <barrido.h>


/* Función auxiliar para barrer temperaturas */
double bar_get_T(double x) {
    /*
        Esta función es monótona creeciente de [0, 1] en [0, 3.3] y crece más
        lentamente cerca de T_c (aproximadamente 2.2676), de forma que convierte
        un muestreo uniforme del [0, 1] en un muestreo por importancia del
        intervalo [0, 3.3].
    */

    // TODO Reemplazar por una función diferente
    return b * x;

}


/* Barremos tempreaturas en [a, b] y llenamos un buffer de promedios */
void bar_get_promedios(modelo *m, int N, int n, promedios *buffer) {
    /*
        Barremos las tempreaturas T en [0, 3.3] con n puntos calculados según
        la función bar_get_T y para cada temperatura calculamos varios promedios
        con integración montecarlo de N pasos (usando Metrópolis).
    */

    double T;
    for (int i = 0; i < N; ++i) {

        // Calculamos la temperatura correspondiente en el barrido
        T = bar_get_T((double) i / N);

        // Setteamos esta temperatura en el modelo
        modelo_reset_T(m, T);

        // Reseteamos el modelo
        modelo_reset_ran(m);

        // Calculamos los promedios
        buffer[i] = sim_get_promedios(m, N);

    }

}