#include "GeneradorAleatorio.h"
#include "ConstantesProyecto.h"
#include <cstdlib>
#include <ctime>

static const int TAM_MIN = TAMANO_LISTA_MINIMO;
static const int TAM_MAX = TAMANO_LISTA_MAXIMO;
static const int VAL_MIN = VALOR_ALEATORIO_MINIMO;
static const int VAL_MAX = VALOR_ALEATORIO_MAXIMO;

// Propósito: inicializar la semilla del generador aleatorio una única vez durante el ciclo de vida del programa.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(1).
GeneradorAleatorio::GeneradorAleatorio() {
    static bool sembrada = false;
    if (!sembrada) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        sembrada = true;
    }
}

// Propósito: generar un tamaño aleatorio entre 7 y 15 y poblar la lista con enteros únicos entre 1 y 100.
// Parámetros: lista (referencia a la ListaDoble donde se almacenarán los números generados).
// Retorno: ninguno.
// Complejidad: O(n²), donde n es la cantidad de elementos generados.
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