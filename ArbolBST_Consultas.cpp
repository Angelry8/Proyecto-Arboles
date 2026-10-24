#include "ArbolBST.h"
#include <iostream>

NodoArbol::NodoArbol(int valor) : dato(valor), izquierdo(0), derecho(0) {}

ArbolBST::ArbolBST() : raiz(0) {}

// Auxiliar de Parte 3: inserta recursivamente e ignora duplicados. TODO.
void ArbolBST::insertarRecursivo(NodoArbol*& nodo, int valor) {
    (void)nodo;
    (void)valor;
    // TODO (Parte 3): insertar en el enlace correspondiente o crear el nodo.
}

// Auxiliar de Parte 3: retorna la cantidad del subárbol. TODO.
int ArbolBST::contarNodos(const NodoArbol* nodo) const {
    (void)nodo;
    // TODO (Parte 3): contar recursivamente ambos subárboles.
    return 0;
}

// Auxiliar de Parte 3: busca el valor y deja su padre en padre. TODO.
const NodoArbol* ArbolBST::buscarNodo(int valor, const NodoArbol*& padre) const {
    (void)valor;
    padre = 0;
    // TODO (Parte 3): recorrer desde raiz; padre debe ser 0 cuando el hallado es raiz.
    return 0;
}

// Auxiliar de Parte 3: imprime raíz, izquierda y derecha. TODO.
void ArbolBST::preOrdenRecursivo(const NodoArbol* nodo) const {
    (void)nodo;
    // TODO (Parte 3): imprimir recursivamente en preorden.
}

// Auxiliar de Parte 3: imprime izquierda, raíz y derecha. TODO.
void ArbolBST::inOrdenRecursivo(const NodoArbol* nodo) const {
    (void)nodo;
    // TODO (Parte 3): imprimir recursivamente en inorden.
}

// Auxiliar de Parte 3: imprime izquierda, derecha y raíz. TODO.
void ArbolBST::postOrdenRecursivo(const NodoArbol* nodo) const {
    (void)nodo;
    // TODO (Parte 3): imprimir recursivamente en postorden.
}

// Propósito: insertar respetando las comparaciones del ABB. Parámetros: valor.
// Retorno: ninguno. Complejidad: O(h), h es la altura del árbol.
void ArbolBST::insertar(int valor) {
    (void)valor;
    // TODO (Parte 3): insertar en posición ordenada; ignorar duplicados.
}

// Propósito: cargar los datos de la lista en orden. Parámetros: lista origen.
// Retorno: ninguno. Complejidad: O(nh).
void ArbolBST::cargarDesdeLista(const ListaDoble& lista) {
    (void)lista;
    // TODO (Parte 3): recorrer ListaDoble de inicio a fin e insertar cada dato.
}

// Propósito: contar todos los nodos. Parámetros: ninguno. Retorno: cantidad. O(n).
int ArbolBST::cantidadNodos() const {
    // TODO (Parte 3): contar recursivamente desde raiz; vacío debe retornar 0.
    return 0;
}

// Propósito: buscar y clasificar un nodo. Parámetros: valor. Retorno: existencia. O(h).
bool ArbolBST::buscar(int valor) const {
    (void)valor;
    std::cout << "Búsqueda pendiente de implementar.\n";
    // TODO (Parte 3): buscar; informar inexistente o raíz y si es padre u hoja.
    return false;
}

// Propósito: imprimir raíz, izquierda y derecha. Parámetros: ninguno. Retorno: ninguno. O(n).
void ArbolBST::preOrden() const {
    if (raiz == 0) {
        std::cout << "El árbol está vacío.\n";
        return;
    }
    // TODO (Parte 3): recorrer en preorden e imprimir los valores.
}

// Propósito: imprimir izquierda, raíz y derecha. Parámetros: ninguno. Retorno: ninguno. O(n).
void ArbolBST::inOrden() const {
    if (raiz == 0) {
        std::cout << "El árbol está vacío.\n";
        return;
    }
    // TODO (Parte 3): recorrer en inorden e imprimir los valores.
}

// Propósito: imprimir izquierda, derecha y raíz. Parámetros: ninguno. Retorno: ninguno. O(n).
void ArbolBST::postOrden() const {
    if (raiz == 0) {
        std::cout << "El árbol está vacío.\n";
        return;
    }
    // TODO (Parte 3): recorrer en postorden e imprimir los valores.
}
