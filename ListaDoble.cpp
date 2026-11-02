#include "ListaDoble.h"
#include <iostream>

// Propósito: inicializar una lista doblemente enlazada vacía.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(1).
ListaDoble::ListaDoble() : primero(0), ultimo(0), cantidad(0) {}

// Propósito: liberar todos los nodos de la lista enlazada al destruirla.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(n), donde n es la cantidad de nodos.
ListaDoble::~ListaDoble() {
    NodoDoble* actual = primero;
    while (actual != 0) {
        NodoDoble* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    primero = 0;
    ultimo = 0;
    cantidad = 0;
}

// Propósito: agregar un nuevo elemento al final de la lista actualizando enlaces y cantidad.
// Parámetros: valor (entero a insertar).
// Retorno: ninguno.
// Complejidad: O(1).
void ListaDoble::insertarAlFinal(int valor) {
    NodoDoble* nuevo = new NodoDoble(valor);
    if (ultimo == 0) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    cantidad++;
}

// Propósito: verificar si un valor específico ya se encuentra presente en la lista.
// Parámetros: valor (entero buscado).
// Retorno: true si el elemento existe en la lista, false en caso contrario.
// Complejidad: O(n), donde n es la cantidad de nodos en la lista.
bool ListaDoble::contiene(int valor) const {
    for (const NodoDoble* actual = primero; actual != 0; actual = actual->siguiente) {
        if (actual->dato == valor) {
            return true;
        }
    }
    return false;
}

// Propósito: reportar el número actual de nodos almacenados en la lista.
// Parámetros: ninguno.
// Retorno: número entero con la cantidad de elementos.
// Complejidad: O(1).
int ListaDoble::tamano() const {
    return cantidad;
}

// Propósito: mostrar en pantalla el tamaño de la lista y la secuencia de elementos en orden.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(n), donde n es la cantidad de nodos.
void ListaDoble::mostrar() const {
    if (cantidad == 0) {
        std::cout << "Tamano de la lista: 0\n";
        std::cout << "La lista esta vacia.\n";
        return;
    }
    std::cout << "Tamano de la lista: " << cantidad << "\n";
    std::cout << "Elementos: ";
    for (const NodoDoble* actual = primero; actual != 0; actual = actual->siguiente) {
        std::cout << actual->dato;
        if (actual->siguiente != 0) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

// Propósito: retornar el puntero al primer nodo de la lista para permitir la lectura secuencial.
// Parámetros: ninguno.
// Retorno: puntero constante al primer NodoDoble, o 0 si la lista está vacía.
// Complejidad: O(1).
const NodoDoble* ListaDoble::obtenerPrimero() const {
    return primero;
}
