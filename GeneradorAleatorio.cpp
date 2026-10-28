#include "GeneradorAleatorio.h"
#include "ConstantesProyecto.h"
#include <cstdlib>
#include <ctime>

// AJUSTAR: abre ConstantesProyecto.h y reemplaza los números por sus nombres reales.
static const int TAM_MIN = TAMANO_LISTA_MINIMO;
static const int TAM_MAX = TAMANO_LISTA_MAXIMO;
static const int VAL_MIN = VALOR_ALEATORIO_MINIMO;
static const int VAL_MAX = VALOR_ALEATORIO_MAXIMO;

GeneradorAleatorio::GeneradorAleatorio() {
    static bool sembrada = false;
    if (!sembrada) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        sembrada = true;
    }
}

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