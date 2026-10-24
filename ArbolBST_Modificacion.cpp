#include "ArbolBST.h"
#include <iostream>

// Auxiliar de Parte 4: libera recursivamente el subárbol. TODO.
void ArbolBST::liberar(NodoArbol* nodo) {
    (void)nodo;
    // TODO (Parte 4): liberar cada nodo del subárbol.
}

// Auxiliar de Parte 4: retorna la raíz nueva del subárbol tras eliminar. TODO.
NodoArbol* ArbolBST::eliminarRecursivo(NodoArbol* nodo, int valor, bool& eliminado) {
    (void)nodo;
    (void)valor;
    (void)eliminado;
    // TODO (Parte 4): eliminar el valor y devolver la nueva raíz del subárbol.
    return 0;
}

// Auxiliar de Parte 4: obtiene el nodo de menor valor del subárbol. TODO.
NodoArbol* ArbolBST::minimo(NodoArbol* nodo) const {
    (void)nodo;
    // TODO (Parte 4): avanzar por los enlaces izquierdos.
    return 0;
}

// Auxiliar de Parte 4: dibujo rotado 90 grados con indentación por nivel. TODO.
void ArbolBST::dibujar(const NodoArbol* nodo, int nivel) const {
    (void)nodo;
    (void)nivel;
    // TODO (Parte 4): dibujar primero el subárbol derecho y luego el izquierdo.
    // Puede mejorarse el formato si Parte 4 prefiere otro, sin cambiar la firma pública.
}

// Propósito: liberar todos los nodos del ABB. Parámetros: ninguno.
// Retorno: ninguno. Complejidad: O(n).
ArbolBST::~ArbolBST() {
    // TODO (Parte 4): liberar recursivamente todos los nodos y dejar raiz en 0.
}

// Propósito: eliminar un valor. Parámetros: valor. Retorno: true si se eliminó. O(h).
bool ArbolBST::eliminar(int valor) {
    (void)valor;
    std::cout << "Eliminación pendiente de implementar.\n";
    // TODO (Parte 4): tratar cero, uno o dos hijos; dos hijos usa sucesor inorden.
    return false;
}

// Propósito: mostrar el árbol gráficamente. Parámetros: ninguno. Retorno: ninguno. O(n).
void ArbolBST::mostrarArbol() const {
    if (raiz == 0) {
        std::cout << "El árbol está vacío.\n";
        return;
    }
    // TODO (Parte 4): imprimir una representación jerárquica legible en consola.
}
