#include "ArbolBST.h"
#include <cstdio>
#include <iostream>

// Espacios que ocupa cada columna del dibujo (alcanza para números de hasta 3 cifras).
static const int ANCHO_COLUMNA = 4;

// Propósito: contar los nodos de un subárbol para ubicar columnas en el dibujo.
// Parámetros: nodo (raíz del subárbol). Retorno: cantidad de nodos. Complejidad: O(n).
static int contarSubarbol(const NodoArbol* nodo) {
    if (nodo == 0) {
        return 0;
    }
    return 1 + contarSubarbol(nodo->izquierdo) + contarSubarbol(nodo->derecho);
}

// Propósito: calcular cuántos niveles tiene un subárbol.
// Parámetros: nodo (raíz del subárbol). Retorno: altura (0 si está vacío). Complejidad: O(n).
static int altura(const NodoArbol* nodo) {
    if (nodo == 0) {
        return 0;
    }
    int izquierda = altura(nodo->izquierdo);
    int derecha = altura(nodo->derecho);
    return 1 + (izquierda > derecha ? izquierda : derecha);
}

// Propósito: contar las cifras de un número para saber cuánto espacio ocupa.
// Parámetros: valor. Retorno: cantidad de caracteres. Complejidad: O(1).
static int largoNumero(int valor) {
    char texto[12];
    return std::snprintf(texto, sizeof(texto), "%d", valor);
}

// Propósito: recorrer en inorden y anotar en las filas los nodos del nivel buscado.
// La columna de cada nodo es su posición en el recorrido inorden, por eso los menores
// quedan a la izquierda y los mayores a la derecha. La rama ('/' o '\') se pone pegada
// al hijo, y una línea de '_' en la fila de valores la une con el padre.
// Parámetros: nodo actual, nivel del nodo, nivel que se está dibujando, contador de
// columnas, fila de valores y fila de ramas. Retorno: ninguno. Complejidad: O(n).
static void llenarNivel(const NodoArbol* nodo, int nivel, int nivelBuscado, int& columna,
                        char* valores, char* ramas) {
    if (nodo == 0) {
        return;
    }
    llenarNivel(nodo->izquierdo, nivel + 1, nivelBuscado, columna, valores, ramas);

    int miColumna = columna;
    columna++;
    if (nivel == nivelBuscado) {
        int inicio = miColumna * ANCHO_COLUMNA;
        char texto[12];
        int largo = std::snprintf(texto, sizeof(texto), "%d", nodo->dato);
        for (int i = 0; i < largo; i++) {
            valores[inicio + i] = texto[i];
        }
        if (nodo->izquierdo != 0) {
            // el hijo izquierdo queda justo antes de los nodos de su subárbol derecho
            int columnaHijo = miColumna - 1 - contarSubarbol(nodo->izquierdo->derecho);
            int rama = columnaHijo * ANCHO_COLUMNA + largoNumero(nodo->izquierdo->dato);
            ramas[rama] = '/';
            for (int i = rama + 1; i < inicio; i++) {
                valores[i] = '_';
            }
        }
        if (nodo->derecho != 0) {
            // el hijo derecho queda justo después de los nodos de su subárbol izquierdo
            int columnaHijo = miColumna + 1 + contarSubarbol(nodo->derecho->izquierdo);
            int rama = columnaHijo * ANCHO_COLUMNA - 1;
            ramas[rama] = '\\';
            for (int i = inicio + largo; i < rama; i++) {
                valores[i] = '_';
            }
        }
    }

    llenarNivel(nodo->derecho, nivel + 1, nivelBuscado, columna, valores, ramas);
}

// Propósito: imprimir una fila del dibujo sin los espacios sobrantes del final.
// Parámetros: fila (texto) y ancho (tamaño de la fila). Retorno: ninguno. Complejidad: O(ancho).
static void imprimirFila(const char* fila, int ancho) {
    int ultimo = ancho - 1;
    while (ultimo >= 0 && fila[ultimo] == ' ') {
        ultimo--;
    }
    for (int i = 0; i <= ultimo; i++) {
        std::cout << fila[i];
    }
    std::cout << "\n";
}

// Propósito: liberar recursivamente en postorden todos los nodos de un subárbol.
// Primero libera los hijos y al final el nodo, para no perder los enlaces.
// Parámetros: nodo (raíz del subárbol). Retorno: ninguno. Complejidad: O(n).
void ArbolBST::liberar(NodoArbol* nodo) {
    if (nodo == 0) {
        return;
    }
    liberar(nodo->izquierdo);
    liberar(nodo->derecho);
    delete nodo;
}

// Propósito: eliminar un valor del subárbol y devolver la raíz que queda en su lugar.
// Caso 1, sin hijos: se borra el nodo y su lugar queda vacío.
// Caso 2, un hijo: se borra el nodo y su único hijo sube a ocupar su lugar.
// Caso 3, dos hijos: se copia el sucesor inorden (el menor del subárbol derecho) en el
// nodo y luego se elimina el nodo original del sucesor, que tiene a lo sumo un hijo.
// Parámetros: nodo (raíz del subárbol), valor a eliminar, eliminado (queda en true si
// se borró). Retorno: nueva raíz del subárbol. Complejidad: O(h).
NodoArbol* ArbolBST::eliminarRecursivo(NodoArbol* nodo, int valor, bool& eliminado) {
    if (nodo == 0) {
        return 0;
    }
    if (valor < nodo->dato) {
        nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, valor, eliminado);
        return nodo;
    }
    if (valor > nodo->dato) {
        nodo->derecho = eliminarRecursivo(nodo->derecho, valor, eliminado);
        return nodo;
    }

    // Caso 1 y caso 2: con cero o un hijo, el hijo (o nada) toma su lugar.
    if (nodo->izquierdo == 0 || nodo->derecho == 0) {
        NodoArbol* reemplazo = (nodo->izquierdo != 0) ? nodo->izquierdo : nodo->derecho;
        delete nodo;
        eliminado = true;
        return reemplazo;
    }

    // Caso 3: dos hijos, se usa el sucesor inorden.
    NodoArbol* sucesor = minimo(nodo->derecho);
    nodo->dato = sucesor->dato;
    nodo->derecho = eliminarRecursivo(nodo->derecho, sucesor->dato, eliminado);
    return nodo;
}

// Propósito: obtener el nodo con el menor valor de un subárbol.
// En un ABB el menor siempre está bajando solo por la izquierda.
// Parámetros: nodo (raíz del subárbol). Retorno: nodo mínimo, o 0 si está vacío. Complejidad: O(h).
NodoArbol* ArbolBST::minimo(NodoArbol* nodo) const {
    if (nodo == 0) {
        return 0;
    }
    while (nodo->izquierdo != 0) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

// Propósito: dibujar un nivel del árbol: una fila con los valores de ese nivel y, debajo,
// una fila con las ramas que bajan hacia el nivel siguiente.
// Parámetros: nodo (raíz del árbol) y nivel (0 es la raíz). Retorno: ninguno. Complejidad: O(n).
void ArbolBST::dibujar(const NodoArbol* nodo, int nivel) const {
    int ancho = contarSubarbol(nodo) * ANCHO_COLUMNA + ANCHO_COLUMNA;
    char* valores = new char[ancho];
    char* ramas = new char[ancho];
    for (int i = 0; i < ancho; i++) {
        valores[i] = ' ';
        ramas[i] = ' ';
    }

    int columna = 0;
    llenarNivel(nodo, 0, nivel, columna, valores, ramas);

    imprimirFila(valores, ancho);
    if (nivel < altura(nodo) - 1) {
        imprimirFila(ramas, ancho);
    }

    delete[] valores;
    delete[] ramas;
}

// Propósito: liberar todos los nodos del ABB al terminar el programa.
// Parámetros: ninguno. Retorno: ninguno. Complejidad: O(n).
ArbolBST::~ArbolBST() {
    liberar(raiz);
    raiz = 0;
}

// Propósito: eliminar un valor del árbol, informando si existía y qué caso se aplicó.
// La lista doble original no se modifica. Parámetros: valor a eliminar.
// Retorno: true si se eliminó, false si no existía. Complejidad: O(h).
bool ArbolBST::eliminar(int valor) {
    const NodoArbol* padre = 0;
    const NodoArbol* nodo = buscarNodo(valor, padre);
    if (nodo == 0) {
        std::cout << "El elemento " << valor << " no existe en el árbol. No se eliminó nada.\n";
        return false;
    }

    if (nodo->izquierdo == 0 && nodo->derecho == 0) {
        std::cout << "El nodo " << valor << " es una hoja (no tiene hijos): se borra directamente.\n";
    } else if (nodo->izquierdo == 0 || nodo->derecho == 0) {
        const NodoArbol* hijo = (nodo->izquierdo != 0) ? nodo->izquierdo : nodo->derecho;
        std::cout << "El nodo " << valor << " tiene un solo hijo (" << hijo->dato
                  << "): el hijo ocupa su lugar.\n";
    } else {
        std::cout << "El nodo " << valor << " tiene dos hijos: su lugar lo ocupa el sucesor inorden "
                  << minimo(nodo->derecho)->dato << " (el menor de su subárbol derecho).\n";
    }

    bool eliminado = false;
    raiz = eliminarRecursivo(raiz, valor, eliminado);
    int restantes = cantidadNodos();
    std::cout << "El elemento " << valor << " fue eliminado. Nodos restantes en el árbol: "
              << restantes << ".\n";
    return eliminado;
}

// Propósito: mostrar el árbol de arriba hacia abajo, un nivel por fila, con la raíz arriba.
// Parámetros: ninguno. Retorno: ninguno. Complejidad: O(n * h).
void ArbolBST::mostrarArbol() const {
    if (raiz == 0) {
        std::cout << "El árbol está vacío.\n";
        return;
    }
    std::cout << "Árbol binario de búsqueda:\n\n";
    int niveles = altura(raiz);
    for (int nivel = 0; nivel < niveles; nivel++) {
        dibujar(raiz, nivel);
    }
}
