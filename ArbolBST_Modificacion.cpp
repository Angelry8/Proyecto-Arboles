#include "ArbolBST.h"
#include <iostream>

// Propósito: liberar de forma recursiva en postorden todos los nodos de un subárbol.
// Parámetros: nodo (puntero a la raíz del subárbol a liberar).
// Retorno: ninguno.
// Complejidad: O(n), donde n es el número de nodos del subárbol.
void ArbolBST::liberar(NodoArbol* nodo) {
    if (nodo != 0) {
        liberar(nodo->izquierdo);
        liberar(nodo->derecho);
        delete nodo;
    }
}

// Propósito: eliminar recursivamente un valor en el subárbol manejando los 3 casos (0, 1 o 2 hijos).
// Parámetros: nodo (puntero al nodo actual), valor (entero a eliminar), eliminado (referencia a booleano de éxito).
// Retorno: puntero a la nueva raíz del subárbol tras la eliminación.
// Complejidad: O(h), donde h es la altura del árbol.
NodoArbol* ArbolBST::eliminarRecursivo(NodoArbol* nodo, int valor, bool& eliminado) {
    if (nodo == 0) {
        return 0;
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, valor, eliminado);
    } else if (valor > nodo->dato) {
        nodo->derecho = eliminarRecursivo(nodo->derecho, valor, eliminado);
    } else {
        // Elemento localizado
        eliminado = true;

        // Caso 1: Nodo sin hijos (nodo hoja)
        if (nodo->izquierdo == 0 && nodo->derecho == 0) {
            delete nodo;
            return 0;
        }

        // Caso 2a: Nodo con un solo hijo (solo hijo derecho)
        if (nodo->izquierdo == 0) {
            NodoArbol* temporal = nodo->derecho;
            delete nodo;
            return temporal;
        }

        // Caso 2b: Nodo con un solo hijo (solo hijo izquierdo)
        if (nodo->derecho == 0) {
            NodoArbol* temporal = nodo->izquierdo;
            delete nodo;
            return temporal;
        }

        // Caso 3: Nodo con dos hijos
        // Se reemplaza por el sucesor inorden (el menor del subárbol derecho)
        NodoArbol* sucesor = minimo(nodo->derecho);
        nodo->dato = sucesor->dato;
        bool eliminadoSucesor = false;
        nodo->derecho = eliminarRecursivo(nodo->derecho, sucesor->dato, eliminadoSucesor);
    }
    return nodo;
}

// Propósito: encontrar y retornar el nodo con el valor mínimo en un subárbol (el nodo más a la izquierda).
// Parámetros: nodo (puntero a la raíz del subárbol).
// Retorno: puntero al nodo con el valor mínimo, o 0 si el subárbol está vacío.
// Complejidad: O(h), donde h es la altura del subárbol.
NodoArbol* ArbolBST::minimo(NodoArbol* nodo) const {
    if (nodo == 0) {
        return 0;
    }
    while (nodo->izquierdo != 0) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

// Propósito: imprimir el ABB en consola rotado 90 grados a la izquierda, con indentación proporcional al nivel.
// Parámetros: nodo (puntero al nodo actual), nivel (profundidad en el árbol para calcular sangría).
// Retorno: ninguno.
// Complejidad: O(n), donde n es el número de nodos del subárbol.
void ArbolBST::dibujar(const NodoArbol* nodo, int nivel) const {
    if (nodo == 0) {
        return;
    }

    dibujar(nodo->derecho, nivel + 1);

    for (int i = 0; i < nivel; ++i) {
        std::cout << "      ";
    }
    std::cout << "[" << nodo->dato << "]\n";

    dibujar(nodo->izquierdo, nivel + 1);
}

// Propósito: liberar toda la memoria dinámica reservada para los nodos del árbol al destruirlo.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(n), donde n es el número de nodos del árbol.
ArbolBST::~ArbolBST() {
    liberar(raiz);
    raiz = 0;
}

// Propósito: eliminar un nodo por su valor, reportar el resultado en pantalla y actualizar la raíz.
// Parámetros: valor (entero que se desea eliminar).
// Retorno: true si el elemento fue encontrado y eliminado, false si no existía.
// Complejidad: O(h), donde h es la altura del árbol.
bool ArbolBST::eliminar(int valor) {
    bool eliminado = false;
    raiz = eliminarRecursivo(raiz, valor, eliminado);
    if (eliminado) {
        std::cout << "El elemento " << valor << " fue eliminado exitosamente del arbol.\n";
    } else {
        std::cout << "El elemento " << valor << " no existe en el arbol. No se pudo eliminar.\n";
    }
    return eliminado;
}

// Propósito: mostrar en consola la estructura jerárquica del árbol o un mensaje si está vacío.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(n).
void ArbolBST::mostrarArbol() const {
    if (raiz == 0) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "\n--- Arbol binario de busqueda (rotado 90 grados, raiz a la izquierda) ---\n";
    dibujar(raiz, 0);
    std::cout << "-------------------------------------------------------------------------\n";
}
