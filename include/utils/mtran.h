#ifndef MTRAN_H
#define MTRAN_H

#include <stdint.h>

#define MTRAN_N 624
#define MTRAN_M 397
#define MTRAN_W 32
#define MTRAN_R 31
#define MTRAN_UMASK (0xFFFFFFFFUL << MTRAN_R)
#define MTRAN_LMASK (0xFFFFFFFFUL >> (MTRAN_W - MTRAN_R))
#define MTRAN_A 0x9908B0DFUL
#define MTRAN_U 11
#define MTRAN_S 7
#define MTRAN_T 15
#define MTRAN_L 18
#define MTRAN_B 0x9D2C5680UL
#define MTRAN_C 0xEFC60000UL
#define MTRAN_F 1812433253UL

typedef struct {
    uint32_t state_array[MTRAN_N];
    int state_index;
} mtran_state;

/* Función para inicializar el generador */
void mtran_set(mtran_state *state, uint32_t seed);

/* Generador Mersenne Twister */
double mtran(void *state);

#endif
