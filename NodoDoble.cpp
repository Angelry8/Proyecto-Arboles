#include "NodoDoble.h"

// Propósito: inicializar un nodo sin enlaces. Parámetros: valor almacenado.
// Retorno: ninguno. Complejidad: O(1).
NodoDoble::NodoDoble(int valor) : dato(valor), anterior(0), siguiente(0) {}
