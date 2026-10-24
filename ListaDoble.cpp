#include "ListaDoble.h"
#include <iostream>

ListaDoble::ListaDoble() : primero(0), ultimo(0), cantidad(0) {}

// Propósito: liberar todos los nodos. Parámetros: ninguno. Retorno: ninguno. O(n).
ListaDoble::~ListaDoble() {
    // TODO (Parte 2): recorrer y liberar cada nodo de la lista.
}

// Propósito: agregar un dato al final. Parámetros: valor entero. Retorno: ninguno. O(1).
void ListaDoble::insertarAlFinal(int valor) {
    (void)valor;
    // TODO (Parte 2): enlazar un nodo nuevo al final y actualizar cantidad.
}

// Propósito: consultar pertenencia. Parámetros: valor. Retorno: true si aparece. O(n).
bool ListaDoble::contiene(int valor) const {
    (void)valor;
    // TODO (Parte 2): recorrer desde primero y comparar los datos.
    return false;
}

// Propósito: reportar cantidad. Parámetros: ninguno. Retorno: cantidad actual. O(1).
int ListaDoble::tamano() const {
    // TODO (Parte 2): devolver el contador de nodos.
    return 0;
}

// Propósito: mostrar tamaño y contenido. Parámetros: ninguno. Retorno: ninguno. O(n).
void ListaDoble::mostrar() const {
    std::cout << "Lista doble (tamaño: " << tamano() << "): ";
    // TODO (Parte 2): imprimir cada elemento en orden desde el primero.
    std::cout << "(sin elementos: método pendiente)\n";
}

// Propósito: entregar el inicio para cargar el ABB. Parámetros: ninguno.
// Retorno: puntero al primer nodo, o 0 si está vacía. Complejidad: O(1).
const NodoDoble* ListaDoble::obtenerPrimero() const {
    // TODO (Parte 2): devolver primero.
    return 0;
}

