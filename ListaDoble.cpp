#include "ListaDoble.h"
#include <iostream>

ListaDoble::ListaDoble() : primero(0), ultimo(0), cantidad(0) {}

// Propósito: liberar todos los nodos. Parámetros: ninguno. Retorno: ninguno. O(n).
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

// Propósito: agregar un dato al final. Parámetros: valor entero. Retorno: ninguno. O(1).
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

// Propósito: consultar pertenencia. Parámetros: valor. Retorno: true si aparece. O(n).
bool ListaDoble::contiene(int valor) const {
    

     for (const NodoDoble* actual = primero; actual != 0; actual = actual->siguiente) {
        if (actual->dato == valor) {
            return true;
        }
    }
    return false;
}

// Propósito: reportar cantidad. Parámetros: ninguno. Retorno: cantidad actual. O(1).
int ListaDoble::tamano() const {
    
    return cantidad;
}

// Propósito: mostrar tamaño y contenido. Parámetros: ninguno. Retorno: ninguno. O(n).
void ListaDoble::mostrar() const {
      if (cantidad == 0) {
        std::cout << "Tamano de la lista: 0" << std::endl;
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }
    std::cout << "Tamano de la lista: " << cantidad << std::endl;
    std::cout << "Elementos: ";
    for (const NodoDoble* actual = primero; actual != 0; actual = actual->siguiente) {
        std::cout << actual->dato;
        if (actual->siguiente != 0) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    

}

// Propósito: entregar el inicio para cargar el ABB. Parámetros: ninguno.
// Retorno: puntero al primer nodo, o 0 si está vacía. Complejidad: O(1).
const NodoDoble* ListaDoble::obtenerPrimero() const {
    
    return primero;
}

