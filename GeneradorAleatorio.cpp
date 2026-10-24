#include "GeneradorAleatorio.h"
#include "ConstantesProyecto.h"

GeneradorAleatorio::GeneradorAleatorio() {
    // TODO (Parte 2): inicializar la semilla una sola vez (srand(time(0)) o <random>).
    // Debe hacerse aquí y no en cargarElementos: llamadas sucesivas no deben
    // reiniciar la secuencia ni repetir valores por compartir la misma marca de tiempo.
}

// Propósito: llenar la lista con valores aleatorios únicos dentro de los rangos.
// Parámetros: lista destino. Retorno: ninguno. Complejidad esperada: O(n²).
void GeneradorAleatorio::cargarElementos(ListaDoble& lista) {
    (void)lista;
    // TODO (Parte 2): elegir tamaño entre TAMANO_LISTA_MINIMO y MAXIMO, generar
    // valores entre VALOR_ALEATORIO_MINIMO y MAXIMO sin repetir y agregarlos.
}
