#include "ArbolBST.h"
#include <iostream>

// Propósito: inicializar un nodo del árbol con un valor dado y sin hijos.
// Parámetros: valor (entero a almacenar).
// Retorno: ninguno.
// Complejidad: O(1).
NodoArbol::NodoArbol(int valor) : dato(valor), izquierdo(0), derecho(0) {}

// Propósito: inicializar un árbol binario de búsqueda vacío.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(1).
ArbolBST::ArbolBST() : raiz(0) {}

// Propósito: insertar un valor de forma recursiva respetando el orden del ABB e ignorando duplicados.
// Parámetros: nodo (referencia al puntero del nodo actual), valor (entero a insertar).
// Retorno: ninguno.
// Complejidad: O(h), donde h es la altura del árbol.
void ArbolBST::insertarRecursivo(NodoArbol*& nodo, int valor) {
    if (nodo == 0) {
        nodo = new NodoArbol(valor);
        return;
    }
    if (valor < nodo->dato) {
        insertarRecursivo(nodo->izquierdo, valor);
    } else if (valor > nodo->dato) {
        insertarRecursivo(nodo->derecho, valor);
    }
    // Si valor == nodo->dato, se ignora el duplicado según la especificación del ABB.
}

// Propósito: contar recursivamente el número total de nodos en un subárbol.
// Parámetros: nodo (puntero al nodo raíz del subárbol).
// Retorno: cantidad de nodos presentes en el subárbol (0 si el nodo es nulo).
// Complejidad: O(n), donde n es el número de nodos del subárbol.
int ArbolBST::contarNodos(const NodoArbol* nodo) const {
    if (nodo == 0) {
        return 0;
    }
    return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
}

// Propósito: buscar un valor en el ABB y actualizar el puntero a su nodo padre.
// Parámetros: valor (entero a buscar), padre (referencia a puntero donde se almacena el padre del nodo hallado, o 0 si es raíz o inexistente).
// Retorno: puntero al nodo encontrado, o 0 si no existe.
// Complejidad: O(h), donde h es la altura del árbol.
const NodoArbol* ArbolBST::buscarNodo(int valor, const NodoArbol*& padre) const {
    padre = 0;
    const NodoArbol* actual = raiz;
    while (actual != 0) {
        if (valor == actual->dato) {
            return actual;
        }
        padre = actual;
        if (valor < actual->dato) {
            actual = actual->izquierdo;
        } else {
            actual = actual->derecho;
        }
    }
    padre = 0;
    return 0;
}

// Propósito: recorrer recursivamente el subárbol en preorden (raíz, izquierdo, derecho) e imprimir cada dato.
// Parámetros: nodo (puntero al nodo actual).
// Retorno: ninguno.
// Complejidad: O(n), donde n es el número de nodos del subárbol.
void ArbolBST::preOrdenRecursivo(const NodoArbol* nodo) const {
    if (nodo != 0) {
        std::cout << nodo->dato << " ";
        preOrdenRecursivo(nodo->izquierdo);
        preOrdenRecursivo(nodo->derecho);
    }
}

// Propósito: recorrer recursivamente el subárbol en inorden (izquierdo, raíz, derecho) e imprimir cada dato.
// Parámetros: nodo (puntero al nodo actual).
// Retorno: ninguno.
// Complejidad: O(n), donde n es el número de nodos del subárbol.
void ArbolBST::inOrdenRecursivo(const NodoArbol* nodo) const {
    if (nodo != 0) {
        inOrdenRecursivo(nodo->izquierdo);
        std::cout << nodo->dato << " ";
        inOrdenRecursivo(nodo->derecho);
    }
}

// Propósito: recorrer recursivamente el subárbol en postorden (izquierdo, derecho, raíz) e imprimir cada dato.
// Parámetros: nodo (puntero al nodo actual).
// Retorno: ninguno.
// Complejidad: O(n), donde n es el número de nodos del subárbol.
void ArbolBST::postOrdenRecursivo(const NodoArbol* nodo) const {
    if (nodo != 0) {
        postOrdenRecursivo(nodo->izquierdo);
        postOrdenRecursivo(nodo->derecho);
        std::cout << nodo->dato << " ";
    }
}

// Propósito: insertar un valor en el ABB respetando el orden e ignorando duplicados.
// Parámetros: valor (entero a insertar).
// Retorno: ninguno.
// Complejidad: O(h), donde h es la altura del árbol.
void ArbolBST::insertar(int valor) {
    insertarRecursivo(raiz, valor);
}

// Propósito: cargar e insertar en el ABB todos los elementos de una ListaDoble en su orden original.
// Parámetros: lista (referencia constante a la lista doblemente enlazada de origen).
// Retorno: ninguno.
// Complejidad: O(nh), donde n es el número de elementos y h la altura del árbol.
void ArbolBST::cargarDesdeLista(const ListaDoble& lista) {
    const NodoDoble* actual = lista.obtenerPrimero();
    while (actual != 0) {
        insertar(actual->dato);
        actual = actual->siguiente;
    }
}

// Propósito: retornar la cantidad total de nodos que contiene el árbol.
// Parámetros: ninguno.
// Retorno: número entero con la cantidad de nodos (0 si está vacío).
// Complejidad: O(n).
int ArbolBST::cantidadNodos() const {
    return contarNodos(raiz);
}

// Propósito: buscar un valor en el árbol, indicar si existe, si es la raíz y si es nodo padre u hoja.
// Parámetros: valor (entero a buscar).
// Retorno: true si el elemento existe en el árbol, false en caso contrario.
// Complejidad: O(h), donde h es la altura del árbol.
bool ArbolBST::buscar(int valor) const {
    const NodoArbol* padre = 0;
    const NodoArbol* nodo = buscarNodo(valor, padre);

    if (nodo == 0) {
        std::cout << "El elemento " << valor << " no existe en el arbol.\n";
        return false;
    }

    bool esRaiz = (padre == 0);
    bool tieneHijos = (nodo->izquierdo != 0 || nodo->derecho != 0);

    std::cout << "El elemento " << valor << " existe en el arbol: ";
    if (esRaiz) {
        if (tieneHijos) {
            std::cout << "es la raiz y es un nodo padre (tiene descendientes).\n";
        } else {
            std::cout << "es la raiz (nodo unico, hoja sin descendientes).\n";
        }
    } else {
        if (tieneHijos) {
            std::cout << "es un nodo padre (no es la raiz y tiene al menos un hijo).\n";
        } else {
            std::cout << "es un nodo hoja (no tiene hijos).\n";
        }
    }

    return true;
}

// Propósito: mostrar el recorrido en preorden (raíz, izquierdo, derecho) de todos los nodos.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(n).
void ArbolBST::preOrden() const {
    if (raiz == 0) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    preOrdenRecursivo(raiz);
    std::cout << "\n";
}

// Propósito: mostrar el recorrido en inorden (izquierdo, raíz, derecho), presentando los valores ordenados.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(n).
void ArbolBST::inOrden() const {
    if (raiz == 0) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    inOrdenRecursivo(raiz);
    std::cout << "\n";
}

// Propósito: mostrar el recorrido en postorden (izquierdo, derecho, raíz) de todos los nodos.
// Parámetros: ninguno.
// Retorno: ninguno.
// Complejidad: O(n).
void ArbolBST::postOrden() const {
    if (raiz == 0) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    postOrdenRecursivo(raiz);
    std::cout << "\n";
}
