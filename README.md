# Laboratorio 4

Reproducimos el modelo de Ising y calculamos algunas variables termodinámicas
usando el método Metrópolis.

# Compilación y ejecución

Para facilitar la compilación y la ejecución de tódos los códigos en este
proyecto, definimos una serie de archivos `makefile` que permiten compilar,
testear, correr, graficar y limpiar todos los programas con los comandos
- `make`
- `make test`
- `make run`
- `make plot`
- `make clean`

Si la terminal esta puesta en el directorio raíz, estos comandos compilan,
testean, corren, grafican y limpian todos los programas del proyecto. Si la
terminal esta puesta en la carpeta correspondiente a algún ejercicio particular,
por ejemplo, en `src/ej1`, entonces se compilan, corren, grafican o limpian
solamente los archivos relacionados con ese ejercicio.

# Estructura de carpetas

En términos generales, cada tipo de archivo involucrado tiene su propia carpeta.
Hay una carpeta para el código de cada ejercicio, así como carpetas para código
de uso común, carpetas para hedaers, para objetos, para binarios, para scripts
de gnuplot, para datos, para imágenes y para el informe.

# Clases y métodos

En `src/utils/` definimos varios structs y funciones (tratamos de hacerlas lo
más general posible) que son útiles para todo el ejercicio. Entre estos hay
- El Mersenne Twister `mtran`
- Un objeto `Modelo`, que representa una matriz de partículas con spin _up_ o
  _down_. Tiene atributos
  - $T^*$ representando la temperatura adimensionalizada
  - $n$ representando el tamaño de la matriz

  tiene 2 constructores: uno inicializando la matriz con todos los spines _up_
  y otro inicializando la matriz con spines aleatorios, y tiene funciones para
  - dar un paso Monte Carlo
  - calcular la magnetización $M$, definida como
    $$M = \sum_{i \in I} s_i.$$
  - calcular la energía $E$, definida como
    $$E = -J \sum_{\langle i, j \rangle} s_i s_j,$$
    donde $J = 1$ en este caso.
- Un objeto `Simulacion`, que representa una evolución de varios pasos Monte
  Carlo de un modelo en particular. Tiene atributos
  - $T^*$ representando la temperatura adimensionalizada
  - $n$ representando el tamaño de la matriz

  tiene 2 constructores: uno inicializando la matriz con todos los spines _up_
  y otro inicializando la matriz con spines aleatorios, y tiene funciones para
  - llenar un buffer de tamaño N con los valores de $M$ a lo largo de N pasos.
  - llenar un buffer de tamaño N con los valores de $E$ a lo largo de N pasos.
  - calcular varios promedios a lo largo de N pasos
    - Magnetización media: $\langle M \rangle$ (es posible que de 0 por
    magnetización espontanea)
    - Magnetización absoluta media: $\langle |M| \rangle$
    - Magnetización cuadrática media: $\langle M^2 \rangle$ (para calcular la
    susceptibilidad)
    - Magnetización cuartica media: $\langle M^4 \rangle$ (para calcular los
    cumulantes de Binder)
    - Energía media: $\langle E \rangle$
    - Energía cuadrática media: $\langle E^2 \rangle$
    - Susceptibilidad: $\chi = \dfrac{1}{T^*} \left(\langle M^2 \rangle - \langle |M| \rangle^2\right)$
    - Calor específico: $C = \left(\dfrac{1}{T^*}\right)^2 \left(\langle E^2 \rangle - \langle E \rangle^2\right)$
    - Cumulante de Binder: $U_L = 1 - \dfrac{\langle M^4 \rangle}{3\langle M^2 \rangle^2}$
    
    para devolver todos estos promedios creamos un struct `promedios` que almacena todas estas variables.
  - resetear la matriz con todos los spines _up_.
  - resetear la matriz con todos los spines aleatorios.
- Un objeto `Barrido` que representa un barrido de temperaturas desde $T_0 = a$
  hasta $T_f = b$. El barrido no es uniforme sinó que los puntos se muestrean
  conforme una distribución (a ser precisada más abajo) que garantiza una mayor
  densidad de puntos cerca de $T_c$.

Como además hay aleatoriedad dando vuelta, el `Modelo` va a necesitar almacenar
también un puntero al estado de algún generador de números aleatorios. En este
caso vamos a usar el Mersenne Twister.
