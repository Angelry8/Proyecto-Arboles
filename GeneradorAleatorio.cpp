#include "GeneradorAleatorio.h"
#include "ConstantesProyecto.h"
#include <cstdlib>
#include <ctime>

// Rangos del enunciado, tomados de ConstantesProyecto.h.
static const int TAM_MIN = TAMANO_LISTA_MINIMO;
static const int TAM_MAX = TAMANO_LISTA_MAXIMO;
static const int VAL_MIN = VALOR_ALEATORIO_MINIMO;
static const int VAL_MAX = VALOR_ALEATORIO_MAXIMO;

// Propósito: sembrar los números aleatorios con la hora, una sola vez por ejecución.
// Parámetros: ninguno. Retorno: ninguno. Complejidad: O(1).
GeneradorAleatorio::GeneradorAleatorio() {
    static bool sembrada = false;
    if (!sembrada) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        sembrada = true;
    }
}

// Propósito: llenar la lista con un tamaño aleatorio entre 7 y 15 y valores únicos entre 1 y 100.
// Si el número sorteado ya está en la lista, se descarta y se sortea otro.
// Parámetros: lista destino. Retorno: ninguno. Complejidad esperada: O(n²).
void GeneradorAleatorio::cargarElementos(ListaDoble& lista) {
    int objetivo = TAM_MIN + std::rand() % (TAM_MAX - TAM_MIN + 1);
    int insertados = 0;
    while (insertados < objetivo) {
        int valor = VAL_MIN + std::rand() % (VAL_MAX - VAL_MIN + 1);
        if (!lista.contiene(valor)) {
            lista.insertarAlFinal(valor);
            insertados++;
        }
    }
}
