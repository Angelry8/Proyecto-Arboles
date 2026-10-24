#ifndef GENERADOR_ALEATORIO_H
#define GENERADOR_ALEATORIO_H

#include "ListaDoble.h"

// Crea el conjunto aleatorio único que sirve de origen al árbol.
class GeneradorAleatorio {
public:
    GeneradorAleatorio();

    // Llena la lista con 7 a 15 enteros únicos entre 1 y 100.
    // Parámetros: lista destino. Retorno: ninguno. Complejidad esperada: O(n²).
    void cargarElementos(ListaDoble& lista);
};

#endif
